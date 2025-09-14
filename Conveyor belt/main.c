#include <stdio.h>
int main() {
    int motors;
    float packageWeight;
    float avgLoad;
    const float maxLoad = 5.6;
printf("How many motors are carrying the packages? ");
scanf("%d", &motors);

printf("How many kg of packages do we expect? ");
scanf("%f", &packageWeight);

avgLoad = packageWeight / motors;


if (avgLoad <= maxLoad) {
    printf("Yes! The conveyor belt can carry the packages.\n");
} else {
    printf("No. The conveyor belt cannot carry the packages.\n");
}
return 0;
}