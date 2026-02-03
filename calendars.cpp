#include <iostream>
#include <vector>

using namespace std;

struct Calendar {
    int p;
    vector<int> days_in_month;
    long long days_in_year;
    vector<long long> prefix_days;
};

vector<Calendar> calendars;

void solve() {
    int NC;
    if (!(cin >> NC)) return;

    calendars.resize(NC + 1);
    for (int i = 1; i <= NC; ++i) {
        cin >> calendars[i].p;
        calendars[i].days_in_month.resize(calendars[i].p + 1);
        calendars[i].days_in_year = 0;
        calendars[i].prefix_days.resize(calendars[i].p + 2, 0);

        long long current_prefix = 0;
        for (int j = 1; j <= calendars[i].p; ++j) {
            cin >> calendars[i].days_in_month[j];
            calendars[i].prefix_days[j] = current_prefix;
            current_prefix += calendars[i].days_in_month[j];
            calendars[i].days_in_year += calendars[i].days_in_month[j];
        }
    }

    int Q;
    cin >> Q;
    for (int q = 1; q <= Q; ++q) {
        int cal1_idx, cal2_idx;
        long long d1, m1, y1;
        cin >> cal1_idx >> cal2_idx >> d1 >> m1 >> y1;

        // Convert to absolute day number (1-based) from Cal 1
        Calendar& c1 = calendars[cal1_idx];
        long long total_days = 0;

        total_days += (y1 - 1) * c1.days_in_year;
        total_days += c1.prefix_days[m1];
        total_days += d1;

        // Convert absolute day number to Cal 2 description
        Calendar& c2 = calendars[cal2_idx];

        long long y2, m2, d2;

        long long days_passed = total_days - 1;
        long long years_passed = days_passed / c2.days_in_year;
        y2 = years_passed + 1;

        long long remainder_days = days_passed % c2.days_in_year;
        long long day_in_year = remainder_days + 1;

        m2 = 1;
        for (int j = 1; j <= c2.p; ++j) {
            if (day_in_year <= c2.days_in_month[j]) {
                m2 = j;
                d2 = day_in_year;
                break;
            } else {
                day_in_year -= c2.days_in_month[j];
            }
        }

        cout << "Query " << q << ": " << d2 << " " << m2 << " " << y2 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
