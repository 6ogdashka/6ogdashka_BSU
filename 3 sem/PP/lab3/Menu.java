import java.text.SimpleDateFormat;
import java.util.*;

public class Menu {
    private static EquipmentStorage storage = new EquipmentStorage();
    private static final String FILENAME = "data.txt";
    private static final SimpleDateFormat SDF = new SimpleDateFormat("MM.yyyy");

    public static void run() {
        Scanner scanner = new Scanner(System.in);
        FileManager.readFromFile(FILENAME, storage);

        while (true) {
            System.out.println("\n--- МЕНЮ ---");
            System.out.println("1. Вывести все элементы (в файл current_info.txt)");
            System.out.println("2. Добавить элемент");
            System.out.println("3. Удалить элемент");
            System.out.println("4. Сортировка по цене");
            System.out.println("5. Сортировка по названию модели");
            System.out.println("6. Сохранить в файл и выйти");
            System.out.print("Выберите пункт: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    storage.printToFile("current_info.txt");
                    System.out.println("Информация успешно выведена в файл current_info.txt");
                    break;
                case 2:
                    try {
                        System.out.print("Тип (1 - Дельтоплан, 2 - Мотоплан): ");
                        int type = scanner.nextInt();
                        scanner.nextLine();
                        System.out.print("ID: ");
                        String id = scanner.nextLine();
                        System.out.print("Код модели: ");
                        String code = scanner.nextLine();
                        System.out.print("Название модели: ");
                        String name = scanner.nextLine();
                        System.out.print("Дата выпуска (MM.yyyy, например 05.2025): ");
                        Date date = SDF.parse(scanner.nextLine());
                        System.out.print("Цена: ");
                        double price = scanner.nextDouble();
                        System.out.print("Макс. вес: ");
                        double weight = scanner.nextDouble();
                        scanner.nextLine();

                        if (type == 1) {
                            System.out.print("Площадь крыла: ");
                            double area = scanner.nextDouble();
                            scanner.nextLine();
                            System.out.print("Материал каркаса: ");
                            String mat = scanner.nextLine();
                            storage.add(new HangGlider(id, code, name, date, price, weight, "", area, mat));
                        } else {
                            System.out.print("Мощность двигателя: ");
                            double pow = scanner.nextDouble();
                            System.out.print("Емкость бака: ");
                            double fuel = scanner.nextDouble();
                            scanner.nextLine();
                            storage.add(new MotorGlider(id, code, name, date, price, weight, "", pow, fuel));
                        }
                        System.out.println("Элемент добавлен.");
                    } catch (Exception e) {
                        System.out.println("Ошибка при добавлении: " + e.getMessage());
                    }
                    break;
                case 3:
                    System.out.print("Введите ID для удаления: ");
                    String delId = scanner.nextLine();
                    storage.remove(delId);
                    System.out.println("Удалено.");
                    break;
                case 4:
                    storage.sortByPrice();
                    System.out.println("Отсортировано по цене.");
                    break;
                case 5:
                    storage.sortByModelName();
                    System.out.println("Отсортировано по названию модели.");
                    break;
                case 6:
                    FileManager.writeToFile(FILENAME, storage);
                    System.out.println("Данные сохранены. Выход.");
                    return;
                default:
                    System.out.println("Неверный выбор.");
            }
        }
    }
}