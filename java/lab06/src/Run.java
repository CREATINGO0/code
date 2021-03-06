public class Run {
    public static void main(String[] args) {
        Part chassis = new Part();
        Part engine  = new Part();
        Part body    = new Part();
        Part turbo   = new Part();
        
        chassis.assignWeight(1.0);
         engine.assignWeight(0.3);
           body.assignWeight(0.7);
          turbo.assignWeight(0.2);
        
        Assembly porsche = new Assembly();
        porsche.add(chassis);
        porsche.add(engine);
        porsche.add(body);

        double porscheWeight = porsche.getWeight();
        System.out.println("porsche weights " + porscheWeight + " tons.");
    }
}