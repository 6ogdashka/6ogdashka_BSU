import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class FileManager {
    private static final String LOG_FILE = "error.log";
    private static final SimpleDateFormat SDF = new SimpleDateFormat("MM.yyyy");

    static {
        SDF.setLenient(false);   // <-- запрещаем "13.2024" и прочий мусор
    }

    public static void readFromFile(String filename, EquipmentStorage storage) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename));
             PrintWriter logWriter = new PrintWriter(new FileWriter(LOG_FILE, true))) {

            String line = reader.readLine();
            int lineNumber = 1;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                try {
                    String[] parts = line.split(";");
                    if (parts.length < 10) {
                        throw new IllegalArgumentException("Недостаточно полей в строке");
                    }

                    String type = parts[0];
                    String id = parts[1];
                    String modelCode = parts[2];
                    String modelName = parts[3];

                    if (!parts[4].matches("(0[1-9]|1[0-2])\\.\\d{4}")) {
                        throw new IllegalArgumentException("Неверный формат месяца/года: " + parts[4]);
                    }
                    Date releaseDate = SDF.parse(parts[4]);

                    double price = Double.parseDouble(parts[5]);
                    double maxWeight = Double.parseDouble(parts[6]);
                    String manual = parts[7];

                    FlyingMachine machine = null;
                    if ("HangGlider".equals(type)) {
                        double sailArea = Double.parseDouble(parts[8]);
                        String frameMaterial = parts[9];
                        machine = new HangGlider(id, modelCode, modelName, releaseDate,
                                                 price, maxWeight, manual, sailArea, frameMaterial);
                    } else if ("MotorGlider".equals(type)) {
                        double enginePower = Double.parseDouble(parts[8]);
                        double fuelCapacity = Double.parseDouble(parts[9]);
                        machine = new MotorGlider(id, modelCode, modelName, releaseDate,
                                                  price, maxWeight, manual, enginePower, fuelCapacity);
                    }

                    if (machine != null) {
                        storage.add(machine);
                    }
                } catch (Exception e) {
                    String errorMsg = "Ошибка в строке " + lineNumber + ": " + e.getMessage();
                    System.out.println(errorMsg);
                    logWriter.println(new Date() + " - " + errorMsg + " | Строка: " + line);
                }
            }
        } catch (IOException e) {
            System.out.println("Ошибка чтения файла: " + e.getMessage());
        }
    }

    public static void writeToFile(String filename, EquipmentStorage storage) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            writer.println("Type;ID;ModelCode;ModelName;ReleaseDate;Price;MaxWeight;Manual;Specific1;Specific2");
            for (FlyingMachine machine : storage.getList()) {
                writer.println(machine.toString());
            }
        } catch (IOException e) {
            System.out.println("Ошибка записи файла: " + e.getMessage());
        }
    }
}