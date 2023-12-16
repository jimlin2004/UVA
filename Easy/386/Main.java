public class Main {
    public static void main(String[] args)
    {
        int[] dp = new int[205];
        for (int i = 1; i <= 200; ++i)
        {
            dp[i] = (i * i * i);
        }

        for (int a = 2; a <= 200; ++a) {
            for (int b = 2; b <= 200; ++b) {
                for (int c = b + 1; c <= 200; ++c) {
                    for (int d = c + 1; d <= 200; ++d) {
                        if (dp[a] == dp[b] + dp[c] + dp[d]) {
                            System.out.printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
                        }
                    }
                }
            }
        }
    }
}