package de.failex.timesync;

import javax.net.ssl.HttpsURLConnection;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class TimeSync {

    static {
        System.load("C:\\Users\\Felix\\gitreps\\TimeSync\\build\\setdate.dll");
    }

    //It is recommended to use your own server / a reliable server
    final static String HOST = "https://felixnaumann.me/api/index.php?action=getdate";

    public static void main(String[] args) throws IOException, ParseException {
        URL requrl = new URL(HOST);
        HttpsURLConnection conn = (HttpsURLConnection) requrl.openConnection();
        boolean dateset = false;

        conn.setRequestMethod("GET");
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

            String line = reader.readLine();
            reader.close();

            System.out.println(line);

            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
            Date date = sdf.parse(line);

            Calendar cal = GregorianCalendar.getInstance();

            cal.setTime(date);

            int day = cal.get(Calendar.DAY_OF_MONTH);
            int month = cal.get(Calendar.MONTH) + 1;
            int year = cal.get(Calendar.YEAR);
            int hour = cal.get(Calendar.HOUR_OF_DAY);
            int min = cal.get(Calendar.MINUTE);
            int sec = cal.get(Calendar.SECOND);
            long epoch = date.getTime();

            System.out.printf("(JAVA) Setting time to %02d.%02d.%d %02d:%02d:%02d (%d)\n", day, month, year, hour, min, sec, epoch);

            dateset = setdate(day, month, year, hour, min, sec, epoch);
        }
        catch(Exception e) {
            e.printStackTrace();
            System.out.println("Unable to get server time. Exiting...");
            System.exit(1);
        }

        if (dateset) {
            System.out.println("New date successfully set!");
        }
    }

    public static native boolean setdate(int day, int month, int year, int hour, int min, int sec, long epoch);
}
