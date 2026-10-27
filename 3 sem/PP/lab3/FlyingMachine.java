import java.text.SimpleDateFormat;
import java.util.Date;

public abstract class FlyingMachine {
    private String id;
    private String modelCode;
    private String modelName;
    private Date releaseDate;
    private double price;
    private double maxWeight;
    private String manual;

    protected static final SimpleDateFormat SDF = new SimpleDateFormat("MM.yyyy");

    public FlyingMachine() {
    }

    public FlyingMachine(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight) {
        this.id = id;
        this.modelCode = modelCode;
        this.modelName = modelName;
        this.releaseDate = releaseDate;
        this.price = price;
        this.maxWeight = maxWeight;
        this.manual = "";
    }

    public FlyingMachine(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight, String manual) {
        this.id = id;
        this.modelCode = modelCode;
        this.modelName = modelName;
        this.releaseDate = releaseDate;
        this.price = price;
        this.maxWeight = maxWeight;
        this.manual = manual;
    }

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }

    public String getModelCode() { return modelCode; }
    public void setModelCode(String modelCode) { this.modelCode = modelCode; }

    public String getModelName() { return modelName; }
    public void setModelName(String modelName) { this.modelName = modelName; }

    public Date getReleaseDate() { return releaseDate; }
    public void setReleaseDate(Date releaseDate) { this.releaseDate = releaseDate; }

    public double getPrice() { return price; }
    public void setPrice(double price) { this.price = price; }

    public double getMaxWeight() { return maxWeight; }
    public void setMaxWeight(double maxWeight) { this.maxWeight = maxWeight; }

    public String getManual() { return manual; }
    public void setManual(String manual) { this.manual = manual; }

    public abstract String getSpecificInfo();

    @Override
    public String toString() {
        return id + ";" + modelCode + ";" + modelName + ";" + 
               (releaseDate != null ? SDF.format(releaseDate) : "01.2026") + ";" + 
               price + ";" + maxWeight + ";" + manual;
    }
}