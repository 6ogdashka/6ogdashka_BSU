import java.util.Date;

public class MotorGlider extends FlyingMachine {
    private double enginePower;
    private double fuelCapacity;

    public MotorGlider() {
        super();
    }

    public MotorGlider(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight, double enginePower, double fuelCapacity) {
        super(id, modelCode, modelName, releaseDate, price, maxWeight);
        this.enginePower = enginePower;
        this.fuelCapacity = fuelCapacity;
    }

    public MotorGlider(String id, String modelCode, String modelName, Date releaseDate, double price, double maxWeight, String manual, double enginePower, double fuelCapacity) {
        super(id, modelCode, modelName, releaseDate, price, maxWeight, manual);
        this.enginePower = enginePower;
        this.fuelCapacity = fuelCapacity;
    }

    public double getEnginePower() { return enginePower; }
    public void setEnginePower(double enginePower) { this.enginePower = enginePower; }

    public double getFuelCapacity() { return fuelCapacity; }
    public void setFuelCapacity(double fuelCapacity) { this.fuelCapacity = fuelCapacity; }

    @Override
    public String getSpecificInfo() {
        return "Мотоплан [Мощность двигателя: " + enginePower + ", Бак: " + fuelCapacity + "]";
    }

    @Override
    public String toString() {
        return "MotorGlider;" + super.toString() + ";" + enginePower + ";" + fuelCapacity;
    }
}