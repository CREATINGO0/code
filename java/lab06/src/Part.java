public class Part implements CarParts {

    /**
     * component: weight
     */
    private double weight;

    /**
     * weight of this part
     */
    public double getWeight() {
        return weight;
    }
    
    public void assignWeight(double aWeight) {
    	weight = aWeight;
    }
}