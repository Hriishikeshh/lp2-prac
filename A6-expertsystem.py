from typing import List, Dict, Any

class InvestmentRecommender:
    def __init__(self):
        # Embedded investment data with all time horizons
        self.investment_data = {
            "stocks": [
                {"name": "AAPL", "sector": "Technology", "performance": 8.7, "risk": 3, "horizon": "Long-term"},
                {"name": "MSFT", "sector": "Technology", "performance": 8.5, "risk": 3, "horizon": "Long-term"},
                {"name": "AMZN", "sector": "E-commerce", "performance": 7.9, "risk": 4, "horizon": "Medium-term"},
                {"name": "TSLA", "sector": "Automotive", "performance": 7.5, "risk": 5, "horizon": "Short-term"},
                {"name": "JPM", "sector": "Banking", "performance": 7.2, "risk": 3, "horizon": "Medium-term"},
                {"name": "RELIANCE", "sector": "Conglomerate", "performance": 8.1, "risk": 3, "horizon": "Long-term"},
                {"name": "TCS", "sector": "IT Services", "performance": 8.3, "risk": 2, "horizon": "Long-term"},
                {"name": "HDFCBANK", "sector": "Banking", "performance": 7.8, "risk": 2, "horizon": "Medium-term"},
                {"name": "INFY", "sector": "IT Services", "performance": 7.6, "risk": 2, "horizon": "Medium-term"},
                {"name": "BHARTIARTL", "sector": "Telecom", "performance": 7.4, "risk": 3, "horizon": "Short-term"},
                {"name": "NVDA", "sector": "Semiconductors", "performance": 9.1, "risk": 4, "horizon": "Short-term"},
                {"name": "PG", "sector": "Consumer Goods", "performance": 6.8, "risk": 2, "horizon": "Long-term"},
                {"name": "V", "sector": "Financial Services", "performance": 7.7, "risk": 3, "horizon": "Medium-term"}
            ],
            "etfs": [
                {"name": "SPY", "sector": "S&P 500 Index", "performance": 8.2, "risk": 2, "horizon": "Long-term"},
                {"name": "QQQ", "sector": "Nasdaq-100 Index", "performance": 8.6, "risk": 3, "horizon": "Medium-term"},
                {"name": "VTI", "sector": "Total Stock Market", "performance": 7.9, "risk": 2, "horizon": "Long-term"},
                {"name": "ARKK", "sector": "Innovation", "performance": 6.8, "risk": 5, "horizon": "Short-term"},
                {"name": "GLD", "sector": "Gold", "performance": 6.5, "risk": 1, "horizon": "Short-term"},
                {"name": "NIFTYBEES", "sector": "Nifty 50 Index", "performance": 7.7, "risk": 2, "horizon": "Medium-term"},
                {"name": "JUNIORBEES", "sector": "Nifty Next 50", "performance": 7.3, "risk": 3, "horizon": "Medium-term"},
                {"name": "BANKBEES", "sector": "Banking Sector", "performance": 7.1, "risk": 3, "horizon": "Short-term"},
                {"name": "GOLDBEES", "sector": "Gold", "performance": 6.2, "risk": 1, "horizon": "Short-term"},
                {"name": "MOM100", "sector": "Momentum Stocks", "performance": 7.0, "risk": 4, "horizon": "Short-term"},
                {"name": "BOND", "sector": "Treasury Bonds", "performance": 5.8, "risk": 1, "horizon": "Long-term"},
                {"name": "DIV", "sector": "Dividend Stocks", "performance": 6.9, "risk": 2, "horizon": "Long-term"}
            ],
            "mutual_funds": [
                {"name": "Vanguard 500 Index", "sector": "Large Cap", "performance": 8.1, "risk": 2, "horizon": "Long-term"},
                {"name": "Fidelity Contrafund", "sector": "Growth", "performance": 7.8, "risk": 3, "horizon": "Medium-term"},
                {"name": "ICICI Pru Bluechip", "sector": "Large Cap", "performance": 7.6, "risk": 2, "horizon": "Long-term"},
                {"name": "SBI Small Cap", "sector": "Small Cap", "performance": 7.2, "risk": 4, "horizon": "Short-term"},
                {"name": "Mirae Asset Large Cap", "sector": "Large Cap", "performance": 7.9, "risk": 2, "horizon": "Medium-term"},
                {"name": "Parag Parikh Flexi Cap", "sector": "Flexi Cap", "performance": 8.0, "risk": 3, "horizon": "Medium-term"},
                {"name": "Axis Midcap", "sector": "Mid Cap", "performance": 7.4, "risk": 3, "horizon": "Short-term"},
                {"name": "PPFAS Flexi Cap", "sector": "Flexi Cap", "performance": 7.7, "risk": 3, "horizon": "Medium-term"},
                {"name": "UTI Nifty Index", "sector": "Index", "performance": 7.5, "risk": 2, "horizon": "Long-term"},
                {"name": "HDFC Balanced Advantage", "sector": "Hybrid", "performance": 7.0, "risk": 2, "horizon": "Short-term"},
                {"name": "Tata Digital India", "sector": "Technology", "performance": 8.3, "risk": 4, "horizon": "Short-term"},
                {"name": "Franklin India Debt", "sector": "Debt", "performance": 6.2, "risk": 1, "horizon": "Long-term"}
            ]
        }
    
    def filter_investments(self, 
                         inv_type: str,
                         sector: str = "", 
                         horizon: str = "", 
                         risk_level: str = "") -> List[Dict[str, Any]]:
        """Filter investments with fallback to broader criteria"""
        investments = self.investment_data.get(inv_type, [])
        
        # Convert risk level to numeric range
        risk_map = {"Low": (1, 2), "Medium": (2, 3), "High": (4, 5)}
        min_risk, max_risk = risk_map.get(risk_level, (1, 5)) if risk_level else (1, 5)
        
        # First try with exact matches
        filtered = []
        for investment in investments:
            sector_match = not sector or investment["sector"].lower() == sector.lower()
            horizon_match = not horizon or investment["horizon"].lower() == horizon.lower()
            risk_match = min_risk <= investment["risk"] <= max_risk
            
            if sector_match and horizon_match and risk_match:
                filtered.append(investment)
        
        # If no exact matches, relax sector first
        if not filtered and sector:
            for investment in investments:
                horizon_match = not horizon or investment["horizon"].lower() == horizon.lower()
                risk_match = min_risk <= investment["risk"] <= max_risk
                
                if horizon_match and risk_match:
                    filtered.append(investment)
        
        # If still no matches, relax horizon
        if not filtered and horizon:
            for investment in investments:
                risk_match = min_risk <= investment["risk"] <= max_risk
                if risk_match:
                    filtered.append(investment)
        
        # If still no matches, just return all of this type
        if not filtered:
            filtered = investments
        
        # Sort by performance (highest first)
        return sorted(filtered, key=lambda x: x["performance"], reverse=True)[:10]  # Limit to top 10
    
    def print_recommendations(self, investments: List[Dict[str, Any]], inv_type: str):
        """Print formatted recommendations with color coding"""
        if not investments:
            print(f"\nNo {inv_type} match your criteria")
            return
        
        print(f"\n\033[1m=== TOP {inv_type.upper()} RECOMMENDATIONS ===\033[0m")
        print(f"{'Name':<30} {'Sector':<20} {'Performance':<12} {'Risk':<10} {'Horizon':<10}")
        print("-" * 85)
        
        for inv in investments:
            # Color coding based on performance
            perf = inv["performance"]
            if perf >= 8.5:
                perf_color = "\033[92m"  # Green
            elif perf >= 7.0:
                perf_color = "\033[93m"  # Yellow
            else:
                perf_color = "\033[91m"  # Red
            
            # Risk level string with color
            risk = inv["risk"]
            if risk <= 2:
                risk_str = "\033[92mLow\033[0m"
            elif risk <= 3:
                risk_str = "\033[93mMedium\033[0m"
            else:
                risk_str = "\033[91mHigh\033[0m"
            
            print(f"{inv['name']:<30} {inv['sector']:<20} {perf_color}{inv['performance']:<12.1f}\033[0m {risk_str:<10} {inv['horizon']:<10}")

    def get_user_input(self):
        """Get user preferences with validation"""
        print("\n\033[1m===== INVESTMENT RECOMMENDATION TOOL =====\033[0m")
        print("Enter your preferences (leave blank for any)\n")
        
        # Get investment types
        while True:
            types_input = input("Which types? (comma separated: stock,etf,mutual_fund or 'all'): ").strip()
            if not types_input or types_input.lower() == "all":
                types = ["stock", "etf", "mutual_fund"]
                break
            
            types = [t.strip().lower() for t in types_input.split(",")]
            valid_types = []
            type_map = {
                "stock": "stock", "stocks": "stock",
                "etf": "etf", "etfs": "etf",
                "mutual": "mutual_fund", "fund": "mutual_fund",
                "mutual_fund": "mutual_fund", "mutual_funds": "mutual_fund"
            }
            
            for t in types:
                if t in type_map:
                    valid_types.append(type_map[t])
            
            if valid_types:
                types = list(set(valid_types))  # Remove duplicates
                break
            print("Invalid input. Please enter stock, etf, and/or mutual_fund")
        
        # Get sector
        sector = input("Preferred sector (e.g., Technology, Banking): ").strip()
        
        # Get horizon with validation
        while True:
            horizon = input("Investment horizon (Short/Medium/Long-term or any): ").strip()
            if not horizon:
                horizon = ""
                break
            horizon = horizon.lower()
            if horizon.startswith("s"):
                horizon = "Short-term"
                break
            elif horizon.startswith("m"):
                horizon = "Medium-term"
                break
            elif horizon.startswith("l"):
                horizon = "Long-term"
                break
            print("Please enter Short, Medium, or Long-term")
        
        # Get risk level with validation
        while True:
            risk_level = input("Risk tolerance (Low/Medium/High or any): ").strip().capitalize()
            if not risk_level or risk_level in ["Low", "Medium", "High"]:
                break
            print("Please enter Low, Medium, or High")
        
        return types, sector, horizon, risk_level

    def recommend(self):
        """Main recommendation flow with guaranteed results"""
        while True:
            types, sector, horizon, risk_level = self.get_user_input()
            
            print("\n\033[1m===== YOUR INVESTMENT RECOMMENDATIONS =====\033[0m")
            
            for inv_type in types:
                # Map to our data keys
                data_key = f"{inv_type}s" if inv_type != "mutual_fund" else "mutual_funds"
                
                filtered = self.filter_investments(
                    inv_type=data_key,
                    sector=sector,
                    horizon=horizon,
                    risk_level=risk_level
                )
                self.print_recommendations(filtered, inv_type)
            
            # Ask to continue
            cont = input("\nWould you like another recommendation? (y/n): ").lower()
            if cont != 'y':
                break

        print("\n\033[1mHappy investing!\033[0m")

# Run the recommender
if __name__ == "__main__":
    recommender = InvestmentRecommender()
    recommender.recommend()