#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
    if(fuel <= 0){
        printf("Mission Failed! LAck of fuel...");
        return;  
    }
    if(planet> totalPlanets){
        printf("Mission Successful!");
        return;
    }
    int remainingFuel = fuel - consumption + recharge;

    if(planet % 4 == 0){
        remainingFuel += solarBonus;
    }
    printf("Planet %d: Fuel remaining = %d\n", planet, remainingFuel);

    calculateFuel(remainingFuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main(){
    int initialFuel = 100;
    int consumption = 33;
    int recharge = 7;
    int solarBonus = 10;
    int startPlanet = 1;
    int totalPlanets = 13;
    calculateFuel(initialFuel, consumption, recharge, solarBonus, startPlanet, totalPlanets);
    return 0;

}