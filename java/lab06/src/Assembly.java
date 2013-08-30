import java.util.*;

public class Assembly implements CarParts {

	    /**
	     * all components
	     */
	    private ArrayList<CarParts> carComponents = new ArrayList<CarParts>();

	    /**
	     * getWeight for whole car
	     */
	    public double getWeight() {
	        double totalWeight = 0;
	        for( CarParts part : carComponents ) {
	            totalWeight += part.getWeight();
	        }
	        return totalWeight;
	    }
	    
	    /**
	     * add items
	     */
	    public void add(CarParts item) {
	    	carComponents.add(item);
	    }

}