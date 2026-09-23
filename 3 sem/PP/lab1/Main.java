import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.Scanner;

class SeriesCalculator {
    public static double calculateSimple(double x, int k) {
        double e = Math.pow(10, -k);
        double sum = 1.0;
        double term = 1.0;
        int n = 1;

        do {
            term = term * (-x) * (2.0 * n - 1.0) / (2.0 * n);
            if (Math.abs(term) >= e) {
                sum += term;
                n++;
            }
        } while (Math.abs(term) >= e);
        
        return sum;
    }

    public static BigDecimal calculateBig(String xStr, int k) {
    // погрешность 10^(-k) через сдвиг точки единицы влево
    BigDecimal e = BigDecimal.ONE.movePointLeft(k);
    
    //конструктор перевода пользовательской строку в BigDecimal
    BigDecimal x = new BigDecimal(xStr);
    
    // нулевой член ряда равен 1, сразу инициализируем 1 и переходим к шагу n = 1
    BigDecimal sum = BigDecimal.ONE;
    BigDecimal term = BigDecimal.ONE;
    int n = 1;

    // точность с запасом и округление вверх
    MathContext mc = new MathContext(k + 5, RoundingMode.HALF_UP);

    do {
        // вычисление члена, 2L это константа типа BigDecimal 
        BigDecimal num = BigDecimal.valueOf(2L * n - 1).multiply(x.negate());
        
        // знаменатель рекуррентного множителя: 2n
        BigDecimal den = BigDecimal.valueOf(2L * n);
        
        // деление с обязательным контекстом mc для избежания бесконечных дробей ( делим num/den)
        BigDecimal multiplier = num.divide(den, mc);
        
        // вычисляем следующее слагаемое через умножение предыдущего на коэффициент
        term = term.multiply(multiplier, mc);
        
        if (term.abs().compareTo(e) >= 0) {
            sum = sum.add(term);
            n++;
        }
    } while (term.abs().compareTo(e) >= 0);
    
    return sum;
}
}

public class Main {
    public static void main(String[] args) throws IOException {
    
        Scanner scanner = new Scanner(System.in);
        System.out.println("--- Ввод для простых типов (double) ---");
        System.out.print("Введите x (-1 < x < 1): ");
        double xDouble = scanner.nextDouble(); // сканер читает дабл
        System.out.print("Введите k (натуральное число): ");
        int kDouble = scanner.nextInt(); //сканер читает инт

        double sumDouble = SeriesCalculator.calculateSimple(xDouble, kDouble); // наш ответ
        
        double standardDouble = 1.0 / Math.sqrt(1.0 + xDouble); //обычный ответ

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("\n--- Ввод для типов BigDecimal ---");
        System.out.print("Введите x (-1 < x < 1): ");
        String xStr = reader.readLine(); // записывает наше огромное число в строку
        System.out.print("Введите k (натуральное число): ");
        int kBig = Integer.parseInt(reader.readLine()); // переводит точность в инт

        BigDecimal sumBig = SeriesCalculator.calculateBig(xStr, kBig); // наш ответ
        double standardBigDouble = 1.0 / Math.sqrt(1.0 + Double.parseDouble(xStr)); // обычный ответ


        System.out.println("\n--- Результаты ---");
        
        int precisionD = kDouble + 1;
        int precisionB = kBig + 1;
        
        System.out.printf("Моя сумма (double)      : %+-20." + precisionD + "f%n", sumDouble); // все это автоматически вызвает класс Formatter
        System.out.printf("Стандартная сумма (double): %+-20." + precisionD + "f%n", standardDouble);
        
        System.out.printf("Моя сумма (BigDecimal)  : %+-20." + precisionB + "f%n", sumBig);
        System.out.printf("Стандартная сумма (Big)   : %+-20." + precisionB + "f%n", standardBigDouble);

        int roundedDouble = (int) Math.round(sumDouble);
        int roundedBig = sumBig.setScale(0, RoundingMode.HALF_UP).intValue();

        System.out.printf("Округленная сумма (double) в 16-ричном: %#X%n", roundedDouble);
        System.out.printf("Округленная сумма (Big) в 8-ричном    : %#o%n", roundedBig);
    }
}