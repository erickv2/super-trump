#include <stdio.h>

typedef struct
{
    char state, card_code[4], city[50];
    int habitants, tourist_attractions;
    float area, pib;
} Card;

float calculateDensity(Card c)
{
    if (c.area == 0)
        return 0;
    return (float)c.habitants / c.area;
}

float calculatePib(Card c)
{
    if (c.area == 0)
        return 0;
    return (float)c.pib / c.habitants;
}

float calculateSuperPower(Card c)
{
    float density = calculateDensity(c);
    float pibPerCapita = calculatePib(c);

    float inverseDensity = (density == 0) ? 0 : 1.0 / density;

    return c.habitants + c.area + c.pib + c.tourist_attractions + pibPerCapita + inverseDensity;
}

void clearBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void compareAttributes(Card c1, Card c2)
{
    float d1 = calculateDensity(c1);
    float d2 = calculateDensity(c2);
    float ppc1 = calculatePib(c1);
    float ppc2 = calculatePib(c2);
    float sp1 = calculateSuperPower(c1);
    float sp2 = calculateSuperPower(c2);

    printf("\nComparação de cards:\n");

    printf("População: Carta %d venceu (%d)\n",
           c1.habitants > c2.habitants ? 1 : 2,
           c1.habitants > c2.habitants ? 1 : 2);

    printf("Área: Carta %d venceu (%d)\n",
           c1.area > c2.area ? 1 : 2,
           c1.area > c2.area ? 1 : 2);

    printf("PIB: Carta %d venceu (%d)\n",
           c1.pib > c2.pib ? 1 : 2,
           c1.pib > c2.pib ? 1 : 2);

    printf("Pontos Turísticos: Carta %d venceu (%d)\n",
           c1.tourist_attractions > c2.tourist_attractions ? 1 : 2,
           c1.tourist_attractions > c2.tourist_attractions ? 1 : 2);

    printf("density populacional: Carta %d venceu (%d)\n",
           d1 < d2 ? 1 : 2,
           d1 < d2 ? 1 : 2);

    printf("PIB per Capita: Carta %d venceu (%d)\n",
           ppc1 > ppc2 ? 1 : 2,
           ppc1 > ppc2 ? 1 : 2);

    printf("Super Poder: Carta %d venceu (%d)\n",
           sp1 > sp2 ? 1 : 2,
           sp1 > sp2 ? 1 : 2);
}

void exibirCarta(Card c, int indice)
{
    printf("\n-- CARTA %d ---\n", indice + 1);
    printf("state: %c\n", c.state);
    printf("Código da carta: %s\n", c.card_code);
    printf("Cidade: %s\n", c.city);
    printf("habitants: %d\n", c.habitants);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Pontos turísticos: %d\n", c.tourist_attractions);
}

void compareSpecificAttributes(Card card1, Card card2, int attribute)
{
    float value1 = 0, value2 = 0;
    const char *attributeName;

    switch (attribute)
    {
    case 1:
        attributeName = "População";
        value1 = card1.habitants;
        value2 = card2.habitants;
        break;
    case 2:
        attributeName = "Área";
        value1 = card1.area;
        value2 = card2.area;
        break;
    case 3:
        attributeName = "PIB";
        value1 = card1.pib;
        value2 = card2.pib;
        break;
    case 4:
        attributeName = "Pontos Turísticos";
        value1 = card1.tourist_attractions;
        value2 = card2.tourist_attractions;
        break;
    case 5:
        attributeName = "Densidade Demográfica";
        value1 = calculateDensity(card1);
        value2 = calculateDensity(card2);
        break;
    default:
        printf("Atributo inválido.\n");
        return;
    }

    printf("\nComparação de cartas (Atributo: %s):\n", attributeName);
    printf("Carta 1 - %s (%c): %.2f\n", card1.city, card1.state, value1);
    printf("Carta 2 - %s (%c): %.2f\n", card2.city, card2.state, value2);

    int result;
    if (attribute == 5) // densidade: menor vence
    {
        result = (value1 < value2) ? 1 : (value1 > value2) ? 2
                                                           : 0;
    }
    else // demais: maior vence
    {
        result = (value1 > value2) ? 1 : (value1 < value2) ? 2
                                                           : 0;
    }

    if (result == 1)
        printf("Resultado: Carta 1 (%s) venceu!\n", card1.city);
    else if (result == 2)
        printf("Resultado: Carta 2 (%s) venceu!\n", card2.city);
    else
        printf("Resultado: Empate!\n");
}

int showComparisonMenu()
{
    int option;
    printf("\n--- MENU DE COMPARAÇÃO ---\n");
    printf("Escolha o atributo para comparar:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Demográfica\n");
    printf("Digite sua opção: ");
    scanf("%d", &option);

    if (option < 1 || option > 5)
    {
        printf("Opção inválida! Comparação não será realizada.\n");
        return -1;
    }

    return option;
}

int main()

{
    Card cards[2];

    for (int i = 0; i < 2; i++)
    {
        printf("\n--- Cadastro da carta %d ---\n", i + 1);

        printf("Digite o estado: \n");
        scanf(" %c", &cards[i].state);
        clearBuffer();

        printf("Digite o código da carta do state: \n");
        scanf(" %3s", cards[i].card_code);

        printf("Digite o nome da cidade do state: \n");
        scanf(" %[^\n]", cards[i].city);

        printf("Digite o número de habitants da cidade: \n");
        scanf("%d", &cards[i].habitants);

        printf("Digite a área da cidade (em km²): \n");
        scanf("%f", &cards[i].area);

        printf("Digite o PIB da cidade: \n");
        scanf("%f", &cards[i].pib);

        printf("Digite o número de pontos turísticos: \n");
        scanf("%d", &cards[i].tourist_attractions);
    }

    for (int i = 0; i < 2; i++)
    {
        exibirCarta(cards[i], i);
        float density = calculateDensity(cards[i]);
        float pibPerCapita = calculatePib(cards[i]);
        printf("density: %.2f habitants/km²\n", density);
        printf("PIB per capita: %.2f \n", pibPerCapita);
    }

    compareAttributes(cards[0], cards[1]);
    int selectedAttribute = showComparisonMenu();
    if (selectedAttribute != -1)
    {
        compareSpecificAttributes(cards[0], cards[1], selectedAttribute);
    }

    return 0;

}