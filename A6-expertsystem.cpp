#include<bits/stdc++.h>
using namespace std;

struct Factor {
    string question;
    int weight;
};

vector<Factor> factors = {
    {"Is the stock showing consistent growth over last 3 years?", 20},
    {"Is the P/E ratio within a healthy range for its sector?", 15},
    {"Is the company fundamentally strong (good revenue/profit)?", 25},
    {"Is the stock undervalued compared to peers?", 20},
    {"Is the industry outlook positive?", 10},
    {"Has there been no major negative news recently?", 10},
    {"Is the stock technically in uptrend?", 10},
    {"Are institutional investors increasing their stake?", 15},
    {"Is dividend yield higher than fixed deposit returns?", 5}
};

void investmentDecision(int score, string& category, string& suggestion) {
    if(score >= 90) {
        category = "Strong Buy";
        suggestion = "Excellent opportunity. You should invest now or increase your position.";
    } else if(score >= 70) {
        category = "Buy";
        suggestion = "Good stock. Safe to invest, consider short to mid-term.";
    } else if(score >= 50) {
        category = "Hold";
        suggestion = "Wait and watch. Might improve soon.";
    } else {
        category = "Sell / Avoid";
        suggestion = "High risk or overvalued. Better to avoid or exit.";
    }
}

void saveToCsv(const string &symbol, const string &sector, const string &horizon, const string &risk,
               int score, const string &category, const string &suggestion, const string &notes) {
    ofstream file("stock_investment_recommendations.csv", ios::app);
    if(file.tellp() == 0) {
        file << "Stock Symbol,Sector,Investment Horizon,Risk Appetite,Score,Category,Suggestion,Analyst Notes\n";
    }
    file << symbol << "," << sector << "," << horizon << "," << risk << ","
         << score << "," << category << "," << suggestion << "," << notes << "\n";
    file.close();
}

int main() {
    string symbol, sector, horizon, risk, notes;
    int score = 0;

    cout << "===== Stock Market Investment Expert System =====\n";
    cout << "Enter stock symbol (e.g., AAPL, INFY): ";
    getline(cin, symbol);

    cout << "Enter sector (e.g., IT, Pharma, Auto): ";
    getline(cin, sector);

    cout << "Investment horizon (Short-term / Long-term): ";
    getline(cin, horizon);

    cout << "Risk appetite (Low / Medium / High): ";
    getline(cin, risk);

    cout << "Answer the following based on your research (Y/N):\n";
    for(const auto &factor : factors) {
        char response;
        while(true) {
            cout << factor.question << " (Y/N): ";
            cin >> response;
            response = toupper(response);
            if(response == 'Y') {
                score += factor.weight;
                break;
            } else if(response == 'N') {
                break;
            } else {
                cout << "Invalid input. Please enter Y or N.\n";
            }
        }
    }
    cin.ignore();

    cout << "\nEnter analyst notes or additional comments: ";
    getline(cin, notes);

    string category, suggestion;
    investmentDecision(score, category, suggestion);

    cout << "\n======= INVESTMENT RECOMMENDATION =======\n";
    cout << "Stock: " << symbol << "\n";
    cout << "Sector: " << sector << "\n";
    cout << "Investment Horizon: " << horizon << "\n";
    cout << "Risk Appetite: " << risk << "\n";
    cout << "Score: " << score << "\n";
    cout << "Category: " << category << "\n";
    cout << "Recommendation: " << suggestion << "\n";
    cout << "Analyst Notes: " << notes << "\n";

    saveToCsv(symbol, sector, horizon, risk, score, category, suggestion, notes);
    cout << "\nRecommendation saved to stock_investment_recommendations.csv\n";

    return 0;
}
