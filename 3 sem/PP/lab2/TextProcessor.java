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

    public static List<String> findTimes(List<String> tokens) throws ParseException {
        List<String> times = new ArrayList<>();
        Pattern p = Pattern.compile("^(0[0-9]|1[0-9]|2[0-3])-(0[0-9]|[0-5][0-9])$");
        SimpleDateFormat sdf = new SimpleDateFormat("HH-mm");
        sdf.setLenient(false);

        for (String token : tokens) {
            if (p.matcher(token).matches()) {
                    Date date = null;
                    date = sdf.parse(token);
                    times.add(sdf.format(date));
            }
        }
        return times;
    }

    public static String insertRandomNumber(String text, String firstExp, String delimiters) {
        StringBuilder sb = new StringBuilder(text);
        double rand = Math.random() * 1000;
        char delim = delimiters.charAt(0);
        String insertStr = delim + String.format(Locale.US, "%.2f", rand) + delim;

        if (firstExp != null) {
            int idx = sb.indexOf(firstExp);
            if (idx != -1) {
                sb.insert(idx + firstExp.length(), insertStr);
                return sb.toString();
            }
        }
    
        int insertIdx = sb.length() / 2;
        while (insertIdx < sb.length() && !(delimiters.contains(String.valueOf(sb.charAt(insertIdx))))) {
            insertIdx++;
        }
        sb.insert(insertIdx, insertStr);
        return sb.toString();
    }

    public static String removeMinLengthSubstrings(String text) {
        Matcher matcher = Pattern.compile("[а-яА-ЯёЁ].*?\\d").matcher(text);
        List<String> matches = new ArrayList<>();
        int minLen = Integer.MAX_VALUE;

        while (matcher.find()) {
            String match = matcher.group();
            matches.add(match);
            if (match.length() < minLen) {
                minLen = match.length();
            }
        }

        StringBuilder sb = new StringBuilder(text);
        for (String match : matches) {
            if (match.length() == minLen) {
                int idx;
                while ((idx = sb.indexOf(match)) != -1) {
                    sb.delete(idx, idx + match.length());
                }
            }
        }
        return sb.toString();
    }
}