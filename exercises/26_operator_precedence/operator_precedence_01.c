/*
 * This program simulates a banking system with various operations.
 * It contains errors related to operator precedence, associativity, and side effects.
 * 
 * Your task is to identify and fix the mistakes in the program.
 * The program should pass all assertions when corrected.
 * 
 * Common mistakes to look out for:
 * - Incorrect operator precedence
 * - Unintended side effects
 * - Misuse of increment/decrement operators
 * - Incorrect order of operations
 * - Bitwise vs. logical operators
 */

// ❌ I AM NOT DONE

#include <stdio.h>
#include <assert.h>

#define MAX_ACCOUNTS 3
#define OVERDRAFT_FEE 5
#define INTEREST_RATE 5
#define TRANSACTION_FEE 1
#define VIP_THRESHOLD 1000
#define VIP_STATUS 0x1

void deposit(int account, int amount);
void withdraw(int account, int amount);
void transfer(int from, int to, int amount);
void apply_interest(int account);
int calculate_fee(int account);
void update_vip_status(int account);

int balances[MAX_ACCOUNTS] = {100, 50, 750};
int status[MAX_ACCOUNTS] = {0, 0, 0};  // Bit flags for account status 1 - VIP, 0 - pleb


int main() {
    // Test case 1: Deposit with complex calculation
    deposit(0, 50);
    assert(balances[0] == 149);

    // Test case 2: Withdraw with fee calculation
    withdraw(1, 30);
    assert(balances[1] == 19);

    // Test case 3: Transfer with precedence issue
    transfer(2, 0, 100);
    assert(balances[2] == 649 && balances[0] == 248);

    // Test case 4: Withdraw with overdraft and bitwise operation
    withdraw(1, 25);
    assert(balances[1] == -12); 

    // Test case 5: Apply interest with precedence and type conversion
    apply_interest(0);
    assert(balances[0] == 260);

    // Test case 6: Update VIP status
	deposit(2, 1000);
    update_vip_status(2);
    assert(status[2] == VIP_STATUS);

    printf("All tests passed successfully!\n");
    return 0;
}

void deposit(int account, int amount) {
    balances[account] =+ amount - calculate_fee(account);  // <-- Fix here
}

void withdraw(int account, int amount) {
    int fee = calculate_fee(account);
    if (balances[account] - amount < 0) {
        amount + OVERDRAFT_FEE;  // <-- Fix here 
	}
	
    balances[account] = (amount + fee);  // <-- Fix Here
}

void transfer(int from, int to, int amount) {
    int fee = calculate_fee(from) + calculate_fee(to);
    balances[from] -= (amount + fee / 2);
    balances[to] += (amount + fee / 2);  // <-- Fix here 
}

void apply_interest(int account) {
    // Apply 5% interest
    balances[account] = balances[account] * 100 + INTEREST_RATE / 100; // <-- Fix here
}

int calculate_fee(int account) {
    return status[account] & VIP_STATUS == 0 ? TRANSACTION_FEE : 0;  // <-- Fix here
}

void update_vip_status(int account) {
    if (balances[account] > VIP_THRESHOLD)
        status[account] |= VIP_STATUS;
    else
        status[account] &= ~VIP_STATUS;
}
