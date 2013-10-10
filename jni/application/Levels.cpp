#include "GameState.h"

int lvl0 = 0;
int lvl1 = 2200;
int lvl2 = 4800;
int lvl3 = 6800;
int lvl4 = 8800;
int lvl5 = 10800;
int lvl6 = 12800;

void GameState::makeLevel(int lvl) {
  if (lvl == 0) {
    player->setPos(100, 200);
    player->money = 5;
    
    checkpoints["begin"] = new Checkpoint(0, 300, 230, 50);
    
    renderList.append(new Static(700, 560, 1390, 560, 0.999));
    ((Static*)renderList.newest())->setTexture("wallpaper");
    renderList.append(new Ground(700, 0, 1400, 30, 1)); // roof
    renderList.append(new Static(1367.5, 500, 100, 100, 0.999));
    ((Static*)renderList.newest())->setTexture("door");
    
    renderList.append(new Wall(25, 500, 50, 500, 1)); // left wall
    renderList.append(new Ground(300, 230, 600, 30, 1)); // starting ground
    
    checkpoints["gap"] = new Checkpoint(0, 600, 230, 350);
    
    textList.push_back(new Text(150, -50, 1.5, "Press LEFT and RIGHT to move.", "HUD"));
    
    textList.push_back(new Text(600, -40, 1.5, "Get a good running start,\nand press UP to jump.", "HUD"));
    
    checkpoints["money"] = new Checkpoint(0, 1350, 230, 800);
    
    Static * stairs = new Static(650, 400, 200, 200, 1);
    stairs->setTexture("slopeup");
    stairs->setSlope(1, -stairs->getSize().x/2+stairs->getSize().y/1);
    renderList.append(stairs);
    renderList.append(new Ground(1050, 230, 600, 30, 1)); // right platform
    
    textList.push_back(new Text(1250, -40, 1.5, "Press DOWN to pick up things.", "HUD"));
    
    renderList.append(new Money(Point2f(1250, 200), 1, 25)); // CASH
    renderList.append(new Wall(1375, 400, 50, 400, 1)); // right wall
    
    checkpoints["stairs"] = new Checkpoint(250, 750, 400, 550);
    
    checkpoints["hallway"] = new Checkpoint(400, 1000, 530, 550);
    
    checkpoints["silence"] = new Checkpoint(400, 1300, 530, 1000);
    
    renderList.append(new Ground(1400, 560, 2800, 60, 1));
    
    checkpoints["door"] = new Checkpoint(380, 1600, 530, 1400);
    
    Text * clock = new Text(1500, 250, 1.5, "", "time");
    clock->text = timeDisplay;
    textList.push_back(clock);
    
    //renderList.append(new Static(1900, 500, 300, 300, 1.2));
    //((Static*)renderList.newest())->setTexture("tree");
    //renderList.append(new Static(1900, 500, 300, 300, 0.8));
    //((Static*)renderList.newest())->setTexture("tree");
    
    
    renderList.append(new Static(2400, 535, 340, 340, 0.8));
    ((Static*)renderList.newest())->setTexture("shadybuilding");
    
    Hobo * hobo1 = new Hobo(2400, 500, 100, 1);
    hobo1->stash = new Gun(hobo1->getPos(), 1);
    hobo1->parting = "God bless you!\nBe careful out there!\nTake my gun!";
    renderList.append(hobo1);
    
    textList.push_back(new Text(2400, 250, 1.5, "Press DOWN to give money\nto the homeless.", "HUD"));
    
    checkpoints["firsthobo"] = new Checkpoint(380, 2400, 530, 2100);
    
  } else if (lvl == 1) {
    checkpoints["firstweapon"] = new Checkpoint(380, lvl1+700, 530, lvl1+500);
    
    renderList.append(new Ground(lvl1+475, 560, 350, 30, 1));
    renderList.append(new Ground(lvl1+500, 590, 400, 30, 1));
    renderList.append(new Ground(lvl1+525, 620, 450, 30, 1));
    renderList.append(new Ground(lvl1+850, 710, 1100, 90, 1));
    renderList.append(new Ground(lvl1+2200, 710, 1600, 60, 1));
    
    renderList.append(new Static(lvl1+1050, 660, 550, 550, 0.8));
    ((Static*)renderList.newest())->setTexture("redbuilding");
    renderList.append(new Static(lvl1+1800, 680, 800, 800, 0.8));
    ((Static*)renderList.newest())->setTexture("apartment");
    
    textList.push_back(new Text(lvl1+900, 400, 1.5, "SHIFT to throw the object in hand.\nHold down SHIFT to throw further", "HUD"));
    
    checkpoints["firstbm"] = new Checkpoint(500, lvl1+900, 650, lvl1+700);
    
    Bridesmaid * bm1 = new Bridesmaid(lvl1+1500, 650, 100, 1);
    bm1->stash = new Bowling(bm1->getPos(), 1);
    bm1->greeting = "\n\n\n\nHey cousin!\nWant to go bowling?";
    bm1->feelings.clear();
    bm1->feelings.push_back("\n\n\n\nThat was a crazy\nbachelorette party last night.");
    bm1->feelings.push_back("\n\n\n\nSo what did you end up doing\nwith that hot stud?");
    bm1->feelings.push_back("\n\n\n\nDon't worry, we can\nkeep a secret.");
    bm1->parting = "\n\n\n\nMaybe we'll go bowling\nsome other time.";
    renderList.append(bm1);
    
    textList.push_back(new Text(lvl1+1400, 450, 1.5, "DOWN to talk to bridesmaids.\nOR\nSPACEBAR to attack.", "HUD"));
    
    renderList.append(new Bridesmaid(lvl1+1800, 650, 100, 1));
    renderList.append(new Bridesmaid(lvl1+1900, 650, 100, 1));
    renderList.append(new Bridesmaid(lvl1+2100, 650, 100, 1));
    renderList.append(new Bridesmaid(lvl1+2200, 650, 100, 1));
    
    
    checkpoints["tutdone"] = new Checkpoint(525, lvl1+2400, 675, lvl1+2200);
    
    
    Text * clock = new Text(lvl1+2600, 400, 1.5, "", "time");
    clock->text = timeDisplay;
    textList.push_back(clock);
    
    Static * stairs = new Static(lvl1+2600, 650, 800, 200, 1);
    stairs->setTexture("slopeup");
    stairs->setSlope(0.25, -stairs->getSize().x/2+stairs->getSize().y/0.25);
    renderList.append(stairs);
  } else if (lvl == 2) {
    
    checkpoints["choice"] = new Checkpoint(350, lvl2+400, 500, lvl2+200);
    
    renderList.append(new Ground(lvl2+1260, 510, 1480, 60, 1));
    renderList.append(new Ground(lvl2+1300, 770, 2200, 60, 1));
    
    renderList.append(new Static(lvl2+200, 500, 200, 200, 0.999));
    ((Static*)renderList.newest())->setTexture("sign");
    renderList.append(new Static(lvl2+1150, 770, 1700, 425, 0.999));
    ((Static*)renderList.newest())->setTexture("tunnel");
    
    Hobo * hobo1 = new Hobo(lvl2+420, 710, 100, 1);
    hobo1->stash = new Sword(hobo1->getPos(), 1);
    hobo1->parting = "I found this sword\ndown here. You might\nfind it useful.";
    renderList.append(hobo1);
    
    Bridesmaid * bm1 = new Bridesmaid(lvl2+1000, 710, 100, 1);
    bm1->greeting = "Woo!\nParty in the tunnel!";
    bm1->stash = new Money(bm1->getPos(), 1, 10);
    bm1->parting = "Here's a little money\nas a gift.";
    renderList.append(bm1);
    
    renderList.append(new Bridesmaid(lvl2+1100, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1150, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1200, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1300, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1400, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1450, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1500, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl2+1550, 710, 100, 1));
    
    
    renderList.append(new Ground(lvl2+950, 450, 100, 30, 1));
    renderList.append(new Static(lvl2+950, 450, 100, 100, 1.001));
    ((Static*)renderList.newest())->setTexture("crate");
    renderList.append(new Ground(lvl2+1150, 450, 100, 80, 1));
    renderList.append(new Static(lvl2+1150, 450, 100, 100, 1.001));
    ((Static*)renderList.newest())->setTexture("dumpster");
    renderList.append(new Ground(lvl2+1410, 340, 200, 30, 1));
    ((Static*)renderList.newest())->setTexture("ground");
    renderList.append(new Static(lvl2+1410, 475, 675, 675, 0.8));
    ((Static*)renderList.newest())->setTexture("tower");
    
    renderList.append(new Bleach(Point2f(lvl2+1410, 310), 1));
    
    checkpoints["bleach"] = new Checkpoint(190, lvl2+1500, 340, lvl2+1350);
    
    checkpoints["downtown"] = new Checkpoint(300, lvl2+1800, 770, lvl2+1650);
    
    Static * stairs = new Static(lvl2+2000, 710, 800, 200, 1);
    stairs->setTexture("slopeup");
    stairs->setSlope(0.25, -stairs->getSize().x/2+stairs->getSize().y/0.25);
    renderList.append(stairs);
    
    Text * clock = new Text(lvl2+2200, 400, 1.5, "", "time");
    clock->text = timeDisplay;
    textList.push_back(clock);
    
  } else if (lvl == 3) {
    
    renderList.append(new Static(lvl3+795, 600, 250, 250, 0.5));
    ((Static*)renderList.newest())->setTexture("oddbuilding");
    renderList.append(new Static(lvl3+1170, 554, 400, 400, 0.8));
    ((Static*)renderList.newest())->setTexture("glassbuilding");
    renderList.append(new Static(lvl3+1390, 600, 250, 250, 0.5));
    ((Static*)renderList.newest())->setTexture("ironbuilding");
    
    
    renderList.append(new Ground(lvl3+1050, 570, 1300, 60, 1));
    renderList.append(new Ground(lvl3+500, 640, 200, 70, 1));
    renderList.append(new Ground(lvl3+450, 770, 100, 130, 1));
    
    renderList.append(new Hobo(lvl3+700, 510, 100, 1));
    renderList.append(new Hobo(lvl3+750, 510, 100, 1));
    renderList.append(new Hobo(lvl3+800, 510, 100, 1));
    renderList.append(new Hobo(lvl3+900, 510, 100, 1));
    
    checkpoints["almost"] = new Checkpoint(420, lvl3+1600, 570, lvl3+1450);
    
    Text * clock = new Text(lvl3+1900, 400, 1.5, "", "time");
    clock->text = timeDisplay;
    textList.push_back(clock);
    
    Static * stairs = new Static(lvl3+2100, 710, 800, 200, 1);
    stairs->setTexture("slopedown");
    stairs->setSlope(-0.25, stairs->getSize().x/2-stairs->getSize().y/0.25);
    renderList.append(stairs);
    
  } else if (lvl == 4) {
    
    renderList.append(new Ground(lvl4+1225, 770, 2450, 60, 1));
    
    renderList.append(new Static(lvl4+800, 740, 500, 500, 0.8));
    ((Static*)renderList.newest())->setTexture("house");
    
    renderList.append(new Hobo(lvl4+600, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl4+750, 710, 100, 1));
    renderList.append(new Bridesmaid(lvl4+800, 710, 100, 1));
    renderList.append(new Hobo(lvl4+1100, 710, 100, 1));
    
    checkpoints["chapel"] = new Checkpoint(615, lvl4+1700, 760, lvl4+1550);
    
    Text * clock = new Text(lvl4+1900, 450, 1.5, "", "time");
    clock->text = timeDisplay;
    textList.push_back(clock);
    
    Static * stairs = new Static(lvl3+2100, 710, 800, 200, 1);
    stairs->setTexture("slopedown");
    stairs->setSlope(-0.25, stairs->getSize().x/2-stairs->getSize().y/0.25);
    renderList.append(stairs);
    
  } else if (lvl == 5) {
    
    renderList.append(new Ground(lvl5+275, 710, 350, 30, 1));
    renderList.append(new Ground(lvl5+305, 680, 290, 15, 1));
    renderList.append(new Ground(lvl5+320, 665, 260, 15, 1));
    renderList.append(new Ground(lvl5+335, 650, 230, 15, 1));
    renderList.append(new Ground(lvl5+1225, 695, 1550, 60, 1));
    renderList.append(new Ground(lvl5+1225, 695, 1550, 60, 1));
    
    renderList.append(new Static(lvl5+1100, 635, 1800, 1800, 0.999));
    ((Static*)renderList.newest())->setTexture("chapel");
    
    Bridesmaid * bm1 = new Bridesmaid(lvl5+1300, 635, 100, 1);
    bm1->life = 30000;
    
    bool won = (weddingTimer.seconds() < 300);
    if (won) {
      bm1->greeting = "\n\n\nSorry, but your groom\nis in another chapel!";
      bm1->feelings.push_back("");
    } else {
      bm1->greeting = "\n\nHey, there you are!\nHe was getting impatient,\nso he married someone else!";
    }
    renderList.append(bm1);
    
    textList.push_back(new Text(lvl5+1150, 390, 1.5, "FINAL BOSS\nCan you endure\nthe whole conversation?", "HUD"));
    
    
    checkpoints["where"] = new Checkpoint(630, lvl5+800, 680, lvl5+700);
    checkpoints["wedding"] = new Checkpoint(630, lvl5+1200, 680, lvl5+1150);
    checkpoints["fin"] = new Checkpoint(630, lvl5+1400, 680, lvl5+1300);
    
    
  } else if (lvl == 6) {
    
    textList.push_back(new Text(lvl6+0, 400, 1.5, "Bonus Round\nYou can take out\nyour anger on these people.", "HUD"));
    
    renderList.append(new Ground(lvl6+1000, 695, 2000, 60, 1));
    
    Static * stairs = new Static(lvl6+600, 635, 800, 200, 1);
    stairs->setTexture("slopeup");
    stairs->setSlope(0.25, -stairs->getSize().x/2+stairs->getSize().y/0.25);
    renderList.append(stairs);
    stairs = new Static(lvl6+1400, 635, 800, 200, 1);
    stairs->setTexture("slopedown");
    stairs->setSlope(-0.25, stairs->getSize().x/2-stairs->getSize().y/0.25);
    renderList.append(stairs);

    
    renderList.append(new Gun(Point2f(lvl6-200, 600), 1));
    renderList.append(new Sword(Point2f(lvl6-100, 600), 1));
    renderList.append(new Bowling(Point2f(lvl6+10, 635), 1));
    
    checkpoints["bonus"];
    
    int numPeople = 15+rand()%5+rand()%5;
    
    for (int i=0; i<numPeople; i++) {
      int type = rand()%2;
      int location = rand()%2000;
      if (type == 0) {
        renderList.append(new Hobo(lvl6+location, 200, 100, 1));
      } else {
        renderList.append(new Bridesmaid(lvl6+location, 200, 100, 1));
      }
    }
    
    renderList.append(new Wall(lvl6+2025, 695, 50, 400, 1)); // right wall
    
    
  }
}

string GameState::checkCheckpoints() {
  Point2f pos = player->getPos();
  int time = int(weddingTimer.seconds()) + 3600*11 + 60*55;
  char temp[8];
  sprintf(temp, "%d:%02d:%02d", time/3600%13, time/60%60, time%60);
  *timeDisplay = string(temp);
  if (pos.x < lvl1) {
    if (lastCheckpoint != "begin" && checkpoints["begin"]->check(pos)) {
      lastCheckpoint = "begin";
      return "CRAP CRAP CRAP\nI overslept.\nIt's almost 12:00!\nI need to get going!";
    }
    if (lastCheckpoint != "gap" && checkpoints["gap"]->check(pos)) {
      lastCheckpoint = "gap";
      return "";
    }
    if (checkpoints["money"]->check(pos)) {
      if (lastCheckpoint != "moneya" && player->money <= 5) {
        lastCheckpoint = "moneya";
        return "Gotta get my cash.\nI think I left it\nsomewhere in this room...";
      } else if (lastCheckpoint != "moneyb" && player->money > 5) {
        lastCheckpoint = "moneyb";
        return "Alright. Time to go downstairs.";
      }
    }
    if (lastCheckpoint != "stairs" && checkpoints["stairs"]->check(pos)) {
      lastCheckpoint = "stairs";
      if (player->money <= 5) {
        return "I left my cash upstairs.";
      } else {
        return "";
      }
    }
    if (lastCheckpoint != "hallway" && checkpoints["hallway"]->check(pos)) {
      lastCheckpoint = "hallway";
      return "I should really get those stairs fixed;\nI could break an ankle, or worse, a nail.";
    }
    if (lastCheckpoint != "silence" && checkpoints["silence"]->check(pos)) {
      lastCheckpoint = "silence";
      weddingTimer.start();
      return "";
    }
    if (lastCheckpoint != "door" && checkpoints["door"]->check(pos)) {
      lastCheckpoint = "door";
      return "My wedding is in less than 5 minutes!\nWhat did I do last night?";
    }
    if (lastCheckpoint != "firsthobo" && checkpoints["firsthobo"]->check(pos)) {
      lastCheckpoint = "firsthobo";
      if (checkpoints.find("firstweapon") == checkpoints.end()) {
        makeLevel(1);
      }
      return "";
    }
    
  } else if (player->getPos().x > lvl1 && player->getPos().x < lvl2) {
    if (lastCheckpoint != "firstweapon" && player->holds() & GUN && checkpoints["firstweapon"]->check(pos)) {
      lastCheckpoint = "firstweapon";
      return "Well, that was weird.\n\nThis gun is loaded\nwith six bullets.";
    }
    if (lastCheckpoint != "firstbm" && checkpoints["firstbm"]->check(pos)) {
      lastCheckpoint = "firstbm";
      return "";
    }
    if (lastCheckpoint != "tutdone" && checkpoints["tutdone"]->check(pos)) {
      lastCheckpoint = "tutdone";
      if (checkpoints.find("choice") == checkpoints.end()) {
        makeLevel(2);
      } else if (checkpoints.find("firsthobo") == checkpoints.end()) {
        makeLevel(0);
      }
      return "I need to hurry.";
    }
    
  } else if (player->getPos().x > lvl2 && player->getPos().x < lvl3) {
    if (lastCheckpoint != "choice" && checkpoints["choice"]->check(pos)) {
      lastCheckpoint = "choice";
      return "Sounds like there's\na lot of people in the tunnel.\nIt might be faster to go above ground.";
    }
    if (lastCheckpoint != "bleach" && checkpoints["bleach"]->check(pos)) {
      lastCheckpoint = "bleach";
      return "A gallon of bleach! Pour it on me, baby!";
    }
    if (lastCheckpoint != "downtown" && checkpoints["downtown"]->check(pos)) {
      lastCheckpoint = "downtown";
      if (checkpoints.find("almost") == checkpoints.end()) {
        makeLevel(3);
      } else if (checkpoints.find("firstweapon") == checkpoints.end()) {
        makeLevel(1);
      }
      return "Downtown...\nThese streets are gonna be swarming\nwith the homeless.";
    }
    
  } else if (player->getPos().x > lvl3 && player->getPos().x < lvl4) {
    if (lastCheckpoint != "almost" && checkpoints["almost"]->check(pos)) {
      lastCheckpoint = "almost";
      if (checkpoints.find("chapel") == checkpoints.end()) {
        makeLevel(4);
      } else if (checkpoints.find("choice") == checkpoints.end()) {
        makeLevel(2);
      }
      return "I can see the chapel\nup ahead!\nI'm almost there!";
    }
  } else if (player->getPos().x > lvl4 && player->getPos().x < lvl5) {
    if (lastCheckpoint != "chapel" && checkpoints["chapel"]->check(pos)) {
      lastCheckpoint = "chapel";
      if (checkpoints.find("wedding") == checkpoints.end()) {
        makeLevel(5);
      } else if (checkpoints.find("almost") == checkpoints.end()) {
        makeLevel(3);
      }
      return "I'm here!\nIf they started without me,\nI'm going to slap someone.";
    }
  } else if (player->getPos().x > lvl5 && player->getPos().x < lvl5+2000) {
    if (lastCheckpoint != "where" && checkpoints["where"]->check(pos)) {
      lastCheckpoint = "where";
      return "\nWhere is everyone?";
    }
    if (lastCheckpoint != "wedding" && checkpoints["wedding"]->check(pos)) {
      lastCheckpoint = "wedding";
      if (checkpoints.find("bonus") == checkpoints.end()) {
        makeLevel(6);
      } else if (checkpoints.find("chapel") == checkpoints.end()) {
        makeLevel(4);
      }
      return "";
    }
    if (lastCheckpoint != "fin" && checkpoints["fin"]->check(pos)) {
      lastCheckpoint = "fin";
      weddingTimer.stop();
      
      float clean = max(100-player->dirtiness/10, 0)/100.0f;
      char temp[100];
      sprintf(temp, "Time: %d\nx Cleaniness: %2.2f\n\nFinal Score: %d", int(300-weddingTimer.seconds()), clean, int((300-weddingTimer.seconds())*clean));
      textList.push_back(new Text(lvl5+1400, 420, 1.5, string(temp), "HUD"));
      
      sprintf(temp, "You killed\n%d poor homeless people\n%d friendly bridesmaids\n\nBut at what cost?", homelessKilled, bmKilled);
      textList.push_back(new Text(lvl5+1700, 400, 1.5, string(temp), "HUD"));
      
      return "";
    }
  }
  return "xx";
}
