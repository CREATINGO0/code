/***********************************************************************
 **                                                                   **
 **    Machine language simulator                                     **
 **                                                                   **
 **    by Tim Bell (bhat@cs.mu.oz.au)                                 **
 **    November 1994                                                  **
 **                                                                   **
 **    This program simulates the machine language described in       **
 **    Appendix B of                                                  **
 **            Brookshear, J. Glenn,                                  **
 **            "Computer Science: An Overview",                       **
 **            Fourth Edition. Benjamin/Cummings, 1994.               **
 **                                                                   **
 **    This program was written to operate in a similar fashion to    **
 **    "Machine Language Simulator Version 2.0C", by J. Glenn         **
 **    Brookshear.  However, the design and coding style are closer   **
 **    to the style preferred in the Melbourne University subject     **
 **    433-142 Computing Fundamentals B.                              **
 **                                                                   **
 **    Modification history:                                          **
 **      10 Oct 1996: fixed rotate bug <bhat@cs.mu.oz.au>             **
 **      21 Sep 1999: fixed address range bug <bhat@cs.mu.oz.au>      **
 **                   (spotted by Travis Downs)                       **
 **                                                                   **
 **    Permission has been granted by the copyright owners for UNSW   **
 **    to use this program in their introductory computing courses.   **
 **                                                                   **
 ***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXMEM          256             /* number of memory cells       */
#define MAXREG          16              /* number of registers          */
#define MAXINT          0x100           /* largest 1-byte +ve integer   */
#define MAXSTEPS        500             /* max number of execution steps*/
#define BUFSIZE         80              /* size of input buffer to use  */
#define OVERFLOWFLAG    0x1000          /* indicates f.p. overflow      */
#define FILESUFFIX      ".mlp"          /* suffix of program files      */
#define FILESUFLEN      4               /* length of suffix             */

#define FALSE           0
#define TRUE            1

/*
 * Instruction opcodes
 */

#define LOADM   0x1
#define LOAD    0x2
#define STOREM  0x3
#define MOVE    0x4
#define ADD     0x5
#define ADDF    0x6
#define OR      0x7
#define AND     0x8
#define XOR     0x9
#define ROT     0xA
#define JUMP    0xB
#define HALT    0xC

/*
 * Execution status values
 */

#define NORMAL          0
#define HALTED          1
#define ERROR           2
#define OVERFLOW        3

/*
 * Instruction:
 *      This type stores a decoded instruction
 */

typedef struct
{
    int opcode;                 /* Opcode field                 */
    int r;                      /* First operand field (reg)    */
    int x;                      /* Second operand field         */
    int y;                      /* Third operand field          */
} Instruction;

/*
 * State:
 *      This type defines the s of the machine at any time
 */

typedef struct
{
    char prog_name[BUFSIZE];    /* Name of current program      */
    int mem[MAXMEM];            /* Contents of memory cells     */
    int reg[MAXREG];            /* Contents of registers        */
    int pc;                     /* Program counter              */
    int ir;                     /* Instruction register         */
    Instruction ins;            /* Decoded instruction          */
    int status;                 /* Execution status             */
} State;

/*
 * Float:
 *      Float is the type of floating point numbers, used after decoding
 */

typedef struct
{
    int sign;
    int exp;
    int mant;
} Float;


/**********************************************************************
 **     Function prototypes                                          **
 **********************************************************************/

int     main(int argc, char *argv[]);
void    process(State *s);
State   *run(State *s, int maxsteps);
State   *step(State *s);
State   *fetch(State *s);
State   *decode(State *s);
State   *execute(State *s);
int     rotate(int r, int y);
int     add_floats(int x, int y);
Float   decode_float(int x);
int     encode_float(Float f);
State   *file_commands(State *s);
char    *check_filename(char *f);
State   *load_program(char *filename);
State   *save_program(State *s, char *filename);
State   *new_s(void);
void    display(State *s);
State   *change_memory(State *s);
State   *change_registers(State *s);
State   *change_pc(State *s);
State   *clear(State *s);
void    display_help(void);
void    error_msg(const char *msg);


/**********************************************************************
 **     Global variable                                              **
 **********************************************************************/

char buffer[BUFSIZE + 1];           /* Buffer used for any input    */


/**********************************************************************
 **     Function definitions                                         **
 **********************************************************************/

/*
 * Main:
 *      Check the command line arguments, initialise program and
 *      start processing.
 */

int
main(int argc, char *argv[])
{
    State *s = NULL;
    
    if (argc > 2)
    {
        fprintf(stderr, "Usage:\n%s [filename]\n", argv[0]);
        exit(1);
    }
    if (argc == 2)
        s = load_program(argv[1]);
    if (s == NULL)
        s = new_s();
    process(s);
    exit(0);
}

/*
 * process:
 *      Prompt the user for input, process the input and
 *      redisplay
 */

void
process(State *s)
{
    int maxsteps = MAXSTEPS;    /* Max steps before stopping    */

    do
    {
        display(s);
        s->status = NORMAL;     /* Reset the machine status     */
        if (fgets(buffer, BUFSIZE, stdin) == NULL)
            buffer[0] = 'Q';
        buffer[0] = toupper(buffer[0]);
        switch (buffer[0])
        {
          case 'M':
            s = change_memory(s);
            break;
          case 'R':
            s = change_registers(s);
            break;
          case 'P':
            s = change_pc(s);
            break;
          case 'C':
            s = clear(s);
            break;
          case 'S':
            s = step(s);
            break;
          case 'G':
            s = run(s, maxsteps);
            break;
          case 'F':
            s = file_commands(s);
            break;
          case 'Q':
            break;
          default:
            display_help();
            break;
        }       
    }
    while (buffer[0] != 'Q');
}



/**********************************************************************
 **     Execution functions                                          **
 **********************************************************************/

/*
 * run:
 *      Execute program for maxsteps cycles or until a halt instruction
 *      is encountered.
 */

State *
run(State *s, int maxsteps)
{
    int steps = 0;
    
    do
    {
        if (steps >= maxsteps)
        {
            printf("\n\n%d machine cycles have been executed.\n"
                   "Continue executing? (Y/N): ", maxsteps);    
            fgets(buffer, BUFSIZE, stdin);
            if (toupper(buffer[0]) == 'N')
                break;
            else
                steps = 0;
        }
        s = step(s);
        steps++;
    }
    while (s->status == NORMAL);
    return s;
}

/*
 * step:
 *      Perform one execution step (cycle)
 */

State *
step(State *s)
{
    s = fetch(s);
    s = decode(s);
    s = execute(s);
    return s;
}

/*
 * fetch:
 *      Fetch the instruction from the memory location specified in the
 *      Program Counter.  Post-increment the PC, wrapping around to
 *      address 0 if past the end of memory.
 *        Note: we assume an instruction does not straddle the end of memory/
 *        start of memory boundary.
 */

State *
fetch(State *s)
{
    s->ir = s->mem[s->pc] * MAXINT + s->mem[s->pc+1];
    s->pc = (s->pc + 2) % MAXMEM;
    return s;
}

/*
 * decode:
 *      Decode the individual fields of the instruction using masking and
 *      bit-shifting.
 */

State *
decode(State *s)
{
    s->ins.opcode = (s->ir & 0xf000) >> 12;
    s->ins.r      = (s->ir & 0x0f00) >> 8;
    s->ins.x      = (s->ir & 0x00f0) >> 4;
    s->ins.y      = (s->ir & 0x000f);
    return s;
}

/*
 * execute:
 *      Execute the instruction specified by the opcode field.  Current
 *      status will change if an invalid instruction is encountered or
 *      the halt instruction is executed.
 */

State *
execute(State *s)
{
    int opcode  = s->ins.opcode;
    int r       = s->ins.r;
    int x       = s->ins.x;
    int y       = s->ins.y;
    
    switch (opcode)
    {
      case LOADM:
          s->reg[r] = s->mem[x * 16 + y];
          break;
      case LOAD:
          s->reg[r] = x * 16 + y;
          break;
      case STOREM:
          s->mem[x * 16 + y] = s->reg[r];
          break;
      case MOVE:
          s->reg[y] = s->reg[x];
          break;
      case ADD:
          s->reg[r] = (s->reg[x] + s->reg[y]) % MAXINT;
          break;
      case ADDF:
          s->reg[r] = add_floats(s->reg[x], s->reg[y]);
          if (s->reg[r] & OVERFLOWFLAG)
          {
              s->reg[r] = s->reg[r] & 0xff;     /* Clear flag */
              s->status = OVERFLOW;
          }
          break;
      case OR:
          s->reg[r] = s->reg[x] | s->reg[y];
          break;
      case AND:
          s->reg[r] = s->reg[x] & s->reg[y];
          break;
      case XOR:
          s->reg[r] = s->reg[x] ^ s->reg[y];
          break;
      case ROT:
          s->reg[r] = rotate(s->reg[r], y);
          break;
      case JUMP:
          if (s->reg[r] == s->reg[0])
              s->pc = x * 16 + y;
          break;
      case HALT:
          s->status = HALTED;
          break;
      default:                          /* Any other instruction is invalid */
          printf("\n\n\n");
          error_msg("Invalid instruction in instruction register");
          s->status = ERROR;
    }
    return s;
}

/*
 * rotate:
 *      Rotate the byte in r by y bits to the right.
 */

int
rotate(int r, int y)
{
    return ((r >> y) | (r << (8 - y))) % MAXINT;
}

/**********************************************************************
 **     Floating Point Functions                                     **
 **********************************************************************/

/*
 * add_floats:
 *      Add two one-byte floating-point numbers.  Underflow -> 0,
 *      Overflow -> +/- 15/16 x 2^3 (with error).
 */

int
add_floats(int x, int y)
{
    Float f, g, h;
    f = decode_float(x);
    g = decode_float(y);
    h.mant = f.mant + g.mant;
    return encode_float(h);
}

/*
 * decode_float:
 *      Decode the one-byte float format into individual fields:
 *              s eee mmmm      s=sign, e=exponent, m=mantissa
 *      The mantissa is given the correct sign, and aligned according
 *      to the exponent field.
 */

Float
decode_float(int x)
{
    Float f;
    f.sign      = (x & 0x80) >> 7;
    f.exp       = (x & 0x70) >> 4; /* Don't convert from excess 4 yet   */
    f.mant      = x & 0x0f;
    if (f.sign)
        f.mant *= -1;
    f.mant <<= f.exp;
    
    return f;
}

/*
 * encode_float:
 *      Given a decoded float, encode to the one-byte format, normalising
 *      the result. Underflow goes to 0, overflow goes to the largest
 *      representable float of the same sign, and an error is signalled.
 *      Rounding is used, and halves round away from zero.
 */

int
encode_float(Float f)
{
    int i = 0;
    int overflow = 0;
    
    if (f.mant < 0)
    {
        f.sign = 1;
        f.mant = - f.mant;
    }
    else
        f.sign = 0;
    while ((f.mant >> i) > 0)           /* find the leftmost 1 bit      */
        i++;
    i -= 4;                             /* allow for 4-bit mantissa     */
    f.mant = (f.mant >> i) +            /* normalise with rounding      */
        ((f.mant >> (i-1)) & 0x01 ? 1 : 0);
    if ((f.mant >> 4) & 0x01)           /* check for rounding overflow  */
    {   
        f.mant >>= 1;                   /* shift to 4 bits again and... */
        i++;                            /* adjust the exponent          */
    }
    if (i > 7)                          /* check for overflow           */
    {
        f.exp = 0x7;
        f.mant = 0xf;
        overflow = OVERFLOWFLAG;
    }
    else if (i < 0)                     /* check for underflow          */
    {
        f.sign = 0;
        f.exp = 0;
        f.mant = 0;
    }
    else
        f.exp = i;
    
    return overflow | (f.sign << 7) | (f.exp << 4) | f.mant;
}


/**********************************************************************
 **     File handling, display and update functions                  **
 **********************************************************************/

/*
 * file_commands:
 *      Display options to retrieve, save and list program files,
 *      and perform appropriate action.
 */

State *
file_commands(State *s)
{
    State *t;
    State *tmp;
    
    printf("\n\nRetrieve or save a program, or list available programs"
           "(R, S, L): ");
    fgets(buffer, BUFSIZE, stdin);
    switch(toupper(buffer[0]))
    {
      case 'R':
        printf("Enter filename: ");
        fgets(buffer, BUFSIZE, stdin);
        t = load_program(check_filename(buffer));
        if (t == NULL)
            error_msg("Program could not be loaded");
        else
        {
            tmp = s;
            s = t;
            free(tmp);
        }
        break;
      case 'S':
        printf("Enter filename: ");
        fgets(buffer, BUFSIZE, stdin);
        t = save_program(s, check_filename(buffer));
        if (t == NULL)
            error_msg("Program could not be saved");
        break;
      case 'L':
        system("ls *" FILESUFFIX);
        printf("Press <Enter> to continue: ");
        fgets(buffer, BUFSIZE, stdin);
        break;
      default:
        break;
    }
    return s;
}

/*
 * check_filename:
 *      Ensure that the filename ends with the appropriate suffix.
 */

char *
check_filename(char *f)
{
    char *t = f;

    while (*t != '\0') 
    {
      if (*t == '\n')
	*t = '\0';
      t++;
    }
    t = f;    
    while (*t != '\0')
        t++;
    t -= FILESUFLEN;
    if (strcmp(t, FILESUFFIX) != 0)
        strcat(f, FILESUFFIX);
    return f;
}

/*
 * load_program:
 *      Load the named program into memory.  Registers and PC are reset
 *      to zero, and the status register set to NORMAL.
 */

State *
load_program(char *filename)
{
    FILE *f;
    State *s;
    int i;
     
    if ((f = fopen(filename, "r")) == NULL)
        return NULL;
    s = malloc(sizeof (State));
    fgets(s->prog_name, BUFSIZE, f);    /* Read program name            */
    for (i = 0; i < MAXMEM; i++)        /* Read memory contents         */
        fscanf(f, "%d", &s->mem[i]);
    fclose(f);
    for (i = 0; i < MAXREG; i++)
        s->reg[i] = 0;
    s->pc = 0;
    s->ir = 0;
    s->status = NORMAL;
    return s;
}

/*
 * save_program:
 *      Save the current program into the given file.  The program's name
 *      is set to the name of the file (without the suffix).
 */

State *
save_program(State *s, char *filename)
{
    FILE *f;
    int name_len;
    int i;
    
    if ((f = fopen(filename, "w")) == NULL)
        return NULL;
    name_len = strlen(filename) - 4;    /* Get len of filename prefix   */
    strncpy(s->prog_name, filename, name_len);
    s->prog_name[name_len] = '\0';
    fprintf(f, "%s", s->prog_name);     /* Write program name           */
    for (i = 0; i < MAXMEM; i++)        /* Write memory contents        */
    {
        if (i % 16 == 0)
            fprintf(f, "\n");
        fprintf(f, "%d ", s->mem[i]);
    }
    fprintf(f, "\n");
    fclose(f);
    return s;
}

/*
 * new_s:
 *      Allocate and initialise a new state structure.
 */

State
*new_s(void)
{
    State *s;
    int i;
    
    s = malloc(sizeof (State));
    for (i = 0; i < MAXMEM; i++)
        s->mem[i] = 0;
    for (i = 0; i < MAXREG; i++)
        s->reg[i] = 0;
    s->pc = 0;
    s->ir = 0;
    s->status = NORMAL;
    strcpy(s->prog_name, "untitled");
    return s;
}

/*
 * display:
 *      Display the machine state.
 */

void
display(State *s)
{
    int i;
    
    printf("\n\n\t\t\tMain Memory: %s\n   ", s->prog_name);
    for (i = 0; i < 0x10; i++)
        printf("   %X", i);
    for (i = 0; i < MAXMEM; i++)
    {
        if (i % 0x10 == 0)
            printf("\n %X ", i / 0x10);
        printf("  %02X", s->mem[i]);
    }
    printf("\n\n");
    for (i = 0; i < MAXREG / 2; i++)
        printf("R%1X:%02X  ", i, s->reg[i]);
    printf("   PC:   %02X\n", s->pc);
    for ( ; i < MAXREG; i++)
        printf("R%1X:%02X  ", i, s->reg[i]);
    printf("   IR: %04X\n", s->ir);
    if (s->status == HALTED)
        printf("Execution halted");
    if (s->status == OVERFLOW)
        printf("Floating point overflow");
    printf("\nCommand (H for help; M, R, P, C, S, G, F, Q): ");
}

/*
 * change_memory:
 *      Prompt the user for details of memory cells to be changed.
 *      Addresses and values are checked for validity, and entry
 *      terminates when no new value is given.
 */

State *
change_memory(State *s)
{
    int address;
    int value;
    
    printf("\n\nAddress of first memory cell to be changed (hex): ");
    fgets(buffer, BUFSIZE, stdin);
    if (sscanf(buffer, "%x", &address) < 1)
        return s;
    if (address < 0 || address >= MAXMEM)
    {
        error_msg("Address out of range");
        return s;
    }
    printf("\n\n"
           "        Cell      Current          New\n"
           "     address     contents     contents\n");
    do
    {
        printf("         %02X           %02X           ",
               address, s->mem[address]);
        fgets(buffer, BUFSIZE, stdin);
        if (sscanf(buffer, "%x", &value) < 1)
            return s;
        if (value >= MAXINT || value < 0)
        {
            error_msg("Value out of range");
            return s;
        }
        s->mem[address++] = value;
    }
    while (address < MAXMEM);
    error_msg("Address too large");
    return s;
}

/*
 * change_registers:
 *      Prompt the user to change the values in registers.  Validity of
 *      register numbers and new values is checked.
 */

State *
change_registers(State *s)
{
    int register_number;
    int value;
    
    do
    {
        printf("\nRegister to change (<Enter> to quit): ");
        fgets(buffer, BUFSIZE, stdin);
        if (sscanf(buffer, "%x", &register_number) < 1)
            return s;
        if (register_number < 0 || register_number > MAXREG)
        {
            error_msg("Register number out of range");
            return s;
        }
        printf("Old value: %02X. New value (<Enter> to keep old value): ",
               s->reg[register_number]);
        fgets(buffer, BUFSIZE, stdin);
        if (sscanf(buffer, "%x", &value) == 1)
        {
            if (value >= MAXINT || value < 0)
            {
                error_msg("Value out of range");
                return s;
            }
            s->reg[register_number] = value;
        }
    }
    while (TRUE);
}

/*
 * change_pc:
 *      Prompt the user to change the value of the program counter.
 *      The validity of the new value is checked, in terms of both
 *      range and alignment (PC values must be even).
 */

State *
change_pc(State *s)
{
    int value;
    
    printf("\nNew value of program counter (<Enter> to keep old value): ");
    fgets(buffer, BUFSIZE, stdin);
    if (sscanf(buffer, "%x", &value) < 1)
        return s;
    if (value >= MAXMEM || value < 0)
    {
        error_msg("Value out of range");
        return s;
    }
    if (value % 2 != 0)
    {
        error_msg("PC must be a multiple of 2");
        return s;
    }
    s->pc = value;
    return s;
}

/*
 * clear:
 *      Prompt the user whether to clear memory, registers or both.
 *      Non-valid input leaves everything unchanged.
 */

State *
clear(State *s)
{
    int i;
    
    printf("\nClear memory, registers, or both? (M, R, or B): ");
    fgets(buffer, BUFSIZE, stdin);
    buffer[0] = toupper(buffer[0]);
    switch (buffer[0])
    {
      case 'M':
        for (i = 0; i < MAXMEM; i++)
            s->mem[i] = 0;
        break;
      case 'R':
        for (i = 0; i < MAXREG; i++)
            s->reg[i] = 0;
        break;
      case 'B':
        for (i = 0; i < MAXMEM; i++)
            s->mem[i] = 0;
        for (i = 0; i < MAXREG; i++)
            s->reg[i] = 0;
        break;
      default:
        error_msg("Nothing cleared");
    }
    return s;
}

/*
 * display_help:
 *      Display the list of options available at the top level.
 */

void
display_help(void)
{
    printf("\n\nOptions are as follows:\n\n"
           "    M  Change contents of memory cells.\n"
           "    R  Change contents of registers.\n"
           "    P  Change contents of program counter.\n"
           "    C  Clear memory or registers.  (Options will be given.)\n"
           "    S  Single step. (Execute a single machine cycle.)\n"
           "    G  Go. (Execute until a halt instruction is executed\n"
           "            or until %d machine cycles have been executed.)\n"
           "    F  List file options (to save or retrieve programs).\n"
           "    H  Display this help screen.\n"
           "    Q  Terminate this simulation program.\n\n\n"
           "\nType <Enter> to return to main display. ", MAXSTEPS);
    fgets(buffer, BUFSIZE, stdin);
}

/*
 * error_msg:
 *      Print the given error message and prompt before continuing.
 */

void
error_msg(const char *msg)
{
    printf("Error: %s. Hit <Enter> to continue:", msg);
    fgets(buffer, BUFSIZE, stdin);
}
