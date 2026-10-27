import java.util.Date;

public class HangGlider extends FlyingMachine {
    private double sailArea;
    private String frameMaterial;

    public HangGlider() {
        super();
    }

    public HangGlider(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight, double sailArea, String frameMaterial) {
        super(id, modelCode, modelName, releaseDate, price, maxWeight);
        this.sailArea = sailArea;
        this.frameMaterial = frameMaterial;
    }

    public HangGlider(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight, String manual, double sailArea, String frameMaterial) {
        super(id, modelCode, modelName, releaseDate, price, maxWeight, manual);
        this.sailArea = sailArea;
        this.frameMaterial = frameMaterial;
    }

    public double getSailArea() { return sailArea; }
    public void setSailArea(double sailArea) { this.sailArea = sailArea; }

    public String getFrameMaterial() { return frameMaterial; }
    public void setFrameMaterial(String frameMaterial) { this.frameMaterial = frameMaterial; }

    @Override
    public String getSpecificInfo() {
        return "Дельтоплан [Площадь крыла: " + sailArea + ", Материал: " + frameMaterial + "]";
    }

    @Override
    public String toString() {
        return "HangGlider;" + super.toString() + ";" + sailArea + ";" + frameMaterial;
    }
}