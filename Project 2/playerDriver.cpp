#include <iostream>
#include "Player.h"

using namespace std;



int main()
{
    // Player player = Player(); //Declare a Player
    // Candy test{"brown candy", "candy born from mud", 1.01, "Buff"};
    // Candy test2{"striped candy", "This candy dropped from the rainbow", 2.02, "Chance"};

    // //print stats before
    // cout << "Stamina before: " << player.getStamina() << endl;
    // cout << "Gold before: " << player.getGold() << endl;
    // cout << "Effect before: " << player.getEffect() << endl;
    // cout << "Inentory before: " << endl;
    // player.printInventory();

    // player.setStamina(5);
    // player.setGold(100);
    // player.setEffect("Increased stamina");
    // player.addCandy(test);
    // player.addCandy(test2);

    // //print stats after
    // cout << "Stamina after: " << player.getStamina() << endl;
    // cout << "Gold after: " << player.getGold() << endl;
    // cout << "Effect after: " << player.getEffect() << endl;
    // cout << "Inentory after: " << endl;
    // player.printInventory();

    //----------------------------------------------------------------------------
    //----------------------------------------------------------------------------

    Candy test{"brown candy", "candy born from mud", 1.01, "Buff"};
    Candy test2{"striped candy", "This candy dropped from the rainbow", 2.02, "Chance"};
    Candy candy_array[3] = {test, test2, test2};
    Player player = Player(5, 100, "Start of game", candy_array, 3);

    //print stats before
    cout << "Stamina before: " << player.getStamina() << endl;
    cout << "Gold before: " << player.getGold() << endl;
    cout << "Effect before: " << player.getEffect() << endl;
    cout << "Inentory before: " << endl;
    player.printInventory();

    
    player.removeCandy("test candy");
    player.removeCandy("striped candy");
    // player.removeCandy("brown candy");
    
    //print stats after
    cout << "Stamina after: " << player.getStamina() << endl;
    cout << "Gold after: " << player.getGold() << endl;
    cout << "Effect after: " << player.getEffect() << endl;
    cout << "Inentory after: " << endl;
    player.printInventory();

    //----------------------------------------------------------------------------
    //----------------------------------------------------------------------------

    // Candy test{"brown candy", "candy born from mud", 1.01, "Buff"};
    // Candy test2{"striped candy", "This candy dropped from the rainbow", 2.02, "Chance"};
    // Candy candy_array[3] = {test, test2, test2};
    // Candy empty[4] = {{}};
    // Player player = Player(5, 100, "No candy!", empty, 4);

    // //print stats before
    // cout << "Stamina before: " << player.getStamina() << endl;
    // cout << "Gold before: " << player.getGold() << endl;
    // cout << "Effect before: " << player.getEffect() << endl;
    // cout << "Inentory before: " << endl;
    // player.printInventory();
    
    // player.addCandy(candy_array[0]);
    
    // //print stats after
    // cout << "Stamina after: " << player.getStamina() << endl;
    // cout << "Gold after: " << player.getGold() << endl;
    // cout << "Effect after: " << player.getEffect() << endl;
    // cout << "Inentory after: " << endl;
    // player.printInventory();

    cout << "Printing inventory through getInventory function" << endl;
    vector<Candy> new_inventory = player.getInventory();

    for (int i = 0; i < int(new_inventory.size()); i++)
    {
        cout << new_inventory.at(i).name << endl;
    }






    return 0;
}