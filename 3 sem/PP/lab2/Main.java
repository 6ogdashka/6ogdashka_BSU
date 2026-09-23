import java.io.*;
import java.util.List;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFilePath));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {

            String textLine = reader.readLine();
            String delimiters = reader.readLine();

            List<String> tokens = TextProcessor.processText(textLine, delimiters);
            
            String[] expNumbers = TextProcessor.findAndSortExpNumbers(tokens);            String firstExp = TextProcessor.getFirstExpToken(tokens);

            List<String> times = TextProcessor.findTimes(tokens);

            String textAfterInsert = TextProcessor.insertRandomNumber(textLine, firstExp);

            String finalText = TextProcessor.removeMinLengthSubstrings(textAfterInsert);

            writer.write("Токены: " + tokens + "\n");
            writer.write("Экспоненциальные числа (отсортированные): " + Arrays.toString(expNumbers) + "\n");
            writer.write("Найденное время: " + times + "\n\n");
            writer.write("Строка после вставки числа:\n" + textAfterInsert + "\n\n");
            writer.write("Результирующая строка (после удаления подстрок):\n" + finalText + "\n\n");

        } catch (IOException e) {
            System.err.println("Ошибка при работе с файлами: " + e.getMessage());
        }
    }
}