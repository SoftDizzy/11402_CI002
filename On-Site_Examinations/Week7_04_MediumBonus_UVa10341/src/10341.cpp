#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// B Bonus

int p, q, r, s, t, u;

double f(double x)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main()
{
    while (cin >> p >> q >> r >> s >> t >> u)
    {
        double left = 0.0;
        double right = 1.0;

        double fLeft = f(left);
        double fRight = f(right);

        if (fLeft == 0)
        {
            cout << fixed << setprecision(4) << left << endl;
        }
        else if (fRight == 0)
        {
            cout << fixed << setprecision(4) << right << endl;
        }
        else if (fLeft * fRight > 0)
        {
            cout << "No solution" << endl;
        }
        else
        {
            for (int i = 0; i < 100; i++)
            {
                double mid = (left + right) / 2.0;
                double fMid = f(mid);

                if (fLeft * fMid > 0)
                {
                    left = mid;
                    fLeft = fMid;
                }
                else
                {
                    right = mid;
                    fRight = fMid;
                }
            }

            double ans = (left + right) / 2.0;
            cout << fixed << setprecision(4) << ans << endl;
        }
    }

    return 0;
}