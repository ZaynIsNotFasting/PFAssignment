#include <stdio.h>
#include <math.h>

double calculateRepaymentRecursive(double loan, double interestRate, double installment, int currentYear, int totalYears) {
    if (currentYear > totalYears) {
        return 0;
    }

    double interest = loan * interestRate;
    double remainingLoan = loan + interest - installment;   
    if (remainingLoan < 0) remainingLoan = 0;

    printf("Year %d: Remaining loan = %.2f\n", currentYear, remainingLoan);

    double futureRepayments = calculateRepaymentRecursive(remainingLoan, interestRate, installment, currentYear + 1, totalYears);
    return installment + futureRepayments;
}

void calculateRepayment(double loan, double interestRate, int years) {
    double r = interestRate;
    double n = (double)years;
    double installment = (r * loan) / (1 - pow(1 + r, -n));

    printf("Loan Amount: %.2f\n", loan);
    printf("Interest Rate: %.0f%%\n", interestRate * 100);
    printf("Duration: %d years\n", years);
    printf("Calculated Fixed Annual Installment: %.2f\n\n", installment);
    printf("Repayment Schedule:\n");

    double totalRepaid = calculateRepaymentRecursive(loan, interestRate, installment, 1, years);

    printf("\nTotal Repayment after %d years: %.2f\n", years, totalRepaid);
}

int main() {
    double loanAmount = 100000.0;
    double interestRate = 0.05;
    int years = 3;

    calculateRepayment(loanAmount, interestRate, years);

    return 0;
}
