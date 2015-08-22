#include "std_lib_facilities.h"

int age_difference(int x, int y);

double yearly_savings_after_inflation(int a, double f, double i, double s, double y);

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);
	char run_again;
	do{
		cout << "Welcome to the retirement calculator!"
			 << "\n\nNote that in this calculator we assume a few things:"
			 << "\n\t-The annual rate of return on savings will be set to 7% per year" //These are conservative estimates
			 << "\n\t and the annual inflation rate set to 3% per year"
			 << "\n\t-Your current salary will be enough for you to live on"
			 << "\n\t during retirement and will be adjusted for inflation"
			 << "\n\t-Your yearly income and savings will go up every year by" 
			 << "\n\t the inflation rate"
			 << "\n\nEnter your current age: ";
		
		int age_curr;
		cin >> age_curr;
		cout << "Enter the age you would like to retire: "; //Desired retirement age
		int age_retire;
		cin >> age_retire;
		cout << "How long would you like your retirement to be (in years): "; //How long you expect your retirement to last
		int length_retire;
		cin >> length_retire; 
		cout << "Enter your current income (in today's dollars): $"; //The amount of income (before inflation) per year you think you'll need in order to fund a comfortable retirement
		double curr_income;
		cin >> curr_income;
		cout << "Enter your current savings: $"; //The current value of your savings and investments
		double curr_savings;
		cin >> curr_savings;
		cout << "Enter amount of money you save per year: $"; //How much money you put into savings, 401k, IRA, etc per year
		double yearly_savings;
		cin >> yearly_savings;
		
		double sav_rate = 0.07;	//Statically setting the rate of return on investments to 6% per year
		double infl_rate = 0.03; //Statically setting the inflation rate to 3% per year
		double eff_rate = ((1 + sav_rate) / (1 + infl_rate)) - 1; //Calculates the effective rate of return
		int age_diff = age_difference(age_retire, age_curr); //Calculates the number of years until you retire
		double future_income = curr_income * pow((1 + infl_rate), age_diff); //Adjusts your income by inflation every year until you hit retirement 
		double future_savings = curr_savings*pow((1 + sav_rate), age_diff); //Calculates how much your initial savings will be worth by the time you're ready to retire
		double req_assets = future_income * (pow((1 + eff_rate), length_retire) - 1) / ((pow((1 + eff_rate), length_retire) * (1 + infl_rate) * eff_rate)); //Calculates the total amount of money you'll need to have saved up by retirement 
		double req_savings = (((req_assets / pow((1 + sav_rate), age_diff)) - curr_savings) * (1 + infl_rate) * pow((1 + eff_rate), age_diff) * eff_rate) / (pow((1 + eff_rate), age_diff) - 1); //Calculates the total amount of money that needs to be saved every year in order to hit your retirement goal
		
		//double yearly_savings_after_inflation(age_diff, future_savings, infl_rate, sav_rate, yearly_savings); //Calls a function that calculates the total value of money put into retirement accounts
		double total_savings = future_savings + yearly_savings_after_inflation(age_diff, future_savings, infl_rate, sav_rate, yearly_savings); //Calculates the total amount of money you'll have by the time you hit retirement age
		double savings_shortfall = abs(req_savings - yearly_savings);	//If there's a shortfall, this determines the additional amount of money you need to save every year to hit your retirement goal
		double savings_gap = req_assets - total_savings; //Calculates the difference between the total amount you'll have saved and the total amount you'll need to retire
		
		cout << "\nOk, here's a summary of your retirement savings:"
			 << "\n\tYou will need $" << req_assets << " to retire comfortably for " << length_retire << " years"
			 << "\n\tYour current savings plan will net you $" << total_savings
			 << "\n\tYou will need to save $" << req_savings << " per year to meet your retirement goal";
		
		if(total_savings < req_assets){ 		
				  	 cout << "\n\tUh oh, looks like you will have a shortfall of $" << savings_gap
					 << "\n\tYou will need to put away an extra $" << savings_shortfall << " per year" << endl;
		}
		else{
			double savings_excess = total_savings - req_assets; //If you are exceeding your retirement goal by putting more into savings every year than required, this calculates how much extra money you are putting away
			cout << "\n\tExcellent! You are meeting or exceeding your savings goal by $" << savings_excess << endl;
			
			if(req_savings < yearly_savings ){
				double yearly_savings_excess = yearly_savings - req_savings;
				cout << "\tYou are saving $" << yearly_savings_excess << " more than required. Keep up the good work!";
			}
			else
				
				cout << "\n\tEven though you hit your retirement goal, you are saving $" << savings_shortfall
					 << "\n\tless per year than is recommended."
					 << "\n\tYour initial savings helped offset this slight savings shortfall"
					 << "\n\tConsider saving some more just in case though"
					 << endl;
		}
		
		
		cout << "\nWould you like to run this program again? (y/n) ";
		cin >> run_again;
		while(run_again != 'Y' && run_again != 'y'){	
			if(run_again == 'N' || run_again == 'n')
				return 0;
			else
				cout << "You entered an invalid character, try again!" << endl;
		}
		cout << endl;
		}while(run_again == 'Y' || run_again == 'y');

}

//This needed to be put into a separate function because the value of age_diff is changed during the yearly_savings_after_inflation calculation
int age_difference(int x, int y){
	int diff = x - y;
	return diff;
}

//Calculates the total value of money put into savings before retirement by increasing your yearly savings by the inflation rate every year
double yearly_savings_after_inflation(int a, double f, double i, double s, double y){
	while (a > 0){
			a -= 1;
			f += y * pow((1 + s), a);
			y *= (1 + i);
		}
	return f;
}
