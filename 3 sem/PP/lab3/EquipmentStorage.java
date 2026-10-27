import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class EquipmentStorage {
    private List<FlyingMachine> list = new ArrayList<>();
    private Map<String, FlyingMachine> map = new HashMap<>();

    public void add(FlyingMachine machine) {
        if (machine != null && machine.getId() != null) {
            list.add(machine);
            map.put(machine.getId(), machine);
        }
    }

    public void remove(String id) {
        FlyingMachine machine = map.remove(id);
        if (machine != null) {
            list.remove(machine);
        }
    }

    public List<FlyingMachine> getList() { return list; }
    public Map<String, FlyingMachine> getMap() { return map; }

    public void sortByPrice() {
        list.sort(Comparator.comparingDouble(FlyingMachine::getPrice));
    }

    public void sortByModelName() {
        list.sort(Comparator.comparing(FlyingMachine::getModelName));
    }

    public void printToFile(String filename) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            writer.println("Type;ID;ModelCode;ModelName;ReleaseDate;Price;MaxWeight;Manual;Specific1;Specific2");
            for (FlyingMachine machine : list) {
                writer.println(machine.toString());
            }
        } catch (IOException e) {
            System.out.println("Ошибка записи файла: " + e.getMessage());
        }
    }
}