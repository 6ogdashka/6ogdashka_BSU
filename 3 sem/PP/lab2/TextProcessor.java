import java.text.*;
import java.util.*;
import java.util.regex.*;

public class TextProcessor {

    public static List<String> processText(String text, String delimiters) {
        List<String> tokens = new ArrayList<>();
        StringTokenizer tokenizer = new StringTokenizer(text, delimiters);
        while (tokenizer.hasMoreTokens()) {
            tokens.add(tokenizer.nextToken());
        }
        return tokens;
    }

    public static String getFirstExpToken(List<String> tokens) {
        String regex = "^[-+]?\\d+(\\.\\d+)?[eE][-+]?\\d+$";
        for (String token : tokens) {
            if (token.matches(regex))
                return token;
        }
        return null;
    }

    public static int ComparatorExp(String s1, String s2) {
        return Double.compare(Double.parseDouble(s1), Double.parseDouble(s2));
    }

    public static String[] findAndSortExpNumbers(List<String> tokens) {
        List<String> list = new ArrayList<>();
        Pattern p = Pattern.compile("^[-+]?\\d+(\\.\\d+)?[eE][-+]?\\d+$"); 
        for (String token : tokens) {
            if (p.matcher(token).matches()) {
                list.add(token);
            }
        }
        String[] arr = list.toArray(new String[0]);
        Arrays.sort(arr, TextProcessor::ComparatorExp);
        return arr;
    }

    public static List<String> findTimes(List<String> tokens) {
        List<String> times = new ArrayList<>();
        Pattern p = Pattern.compile("^(0[0-9]|1[0-9]|2[0-3])-(0[0-9]|[0-5][0-9])$");
        SimpleDateFormat sdf = new SimpleDateFormat("HH-mm");
        sdf.setLenient(false);

        for (String token : tokens) {
            if (!token.matches("^[-+]?\\d+(\\.\\d+)?[eE][-+]?\\d+$") && p.matcher(token).matches()) {
                try {
                    Date date = sdf.parse(token);
                    times.add(sdf.format(date));
                } catch (ParseException ignored) {
                }
            }
        }
        return times;
    }

    public static String insertRandomNumber(String text, String firstExp) {
        StringBuilder sb = new StringBuilder(text);
        double rand = Math.random() * 1000;
        NumberFormat currencyFormat = NumberFormat.getCurrencyInstance(Locale.of("be", "BY"));
        DecimalFormat percentFormat = new DecimalFormat("#.##%");

        String insertStr = String.format(" [Случ: %s | %s] ",
                currencyFormat.format(rand),
                percentFormat.format(rand / 1000.0));

        if (firstExp != null) {
            int idx = sb.indexOf(firstExp);
            if (idx != -1) {
                sb.insert(idx + firstExp.length(), insertStr);
            }
        } else {
            sb.insert(sb.length() / 2, insertStr);
        }
        return sb.toString();
    }

    public static String removeMinLengthSubstrings(String text) {
        StringBuilder sb = new StringBuilder(text);
        Pattern p = Pattern.compile("[а-яА-ЯёЁ].*?\\d");
        Matcher m = p.matcher(sb.toString());

        int minLen = Integer.MAX_VALUE;
        while (m.find()) {
            int currentLen = m.group().length();
            if (currentLen < minLen) {
                minLen = currentLen;
            }
        }

        if (minLen != Integer.MAX_VALUE) {
            m.reset();
            List<int[]> ranges = new ArrayList<>();
            while (m.find()) {
                if (m.group().length() == minLen) {
                    ranges.add(new int[] { m.start(), m.end() });
                }
            }
            for (int i = ranges.size() - 1; i >= 0; i--) {
                sb.delete(ranges.get(i)[0], ranges.get(i)[1]);
            }
        }
        return sb.toString();
    }
}