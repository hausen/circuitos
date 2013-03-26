public class prog2 {
    public static void main(String args[])
    {
        int[][] m = new int[7000][7000];
        long start = System.currentTimeMillis();
        for (int i=0; i<7000; i++)
            for (int j=0; j<7000; j++)
            {
                m[i][j] = 1;
            }
        long stop = System.currentTimeMillis();
        System.out.println("Tempo: " + (stop-start) + "ms");
        start = System.currentTimeMillis();
        for (int i=0; i<7000; i++)
            for (int j=0; j<7000; j++)
            {
                m[j][i] = 1;
            }
        stop = System.currentTimeMillis();
        System.out.println("Tempo: " + (stop-start) + "ms");
    }
}
