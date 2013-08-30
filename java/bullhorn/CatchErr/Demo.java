public class Demo {  

    /** 
     * @param args 
     */  
    public static void main(String[] args) {  
        // TODO Auto-generated method stub  
        try {  
            throw new MyError("My Error");  
        } catch (MyError e) {  
            System.out.println(e.getMessage());  
        }  
    }  

}  

class MyError extends Error {  

    /** 
     *  
     */  
    private static final long serialVersionUID = 1L;  

    public MyError() {  
        super();  
        // TODO Auto-generated constructor stub  
    }  

    public MyError(String message, Throwable cause) {  
        super(message, cause);  
        // TODO Auto-generated constructor stub  
    }  

    public MyError(String message) {  
        super(message);  
        // TODO Auto-generated constructor stub  
    }  

    public MyError(Throwable cause) {  
        super(cause);  
        // TODO Auto-generated constructor stub  
    }  

}  
