#include "Bridesmaid.h"

string brideGreetings[] = {
  "Hey girl!", 
  "OH. MAH. GAHD.\nYou have to\nhear this.", 
  "Nice haircut!", 
  "Do you want\nto know what\nhappened today?", 
  "Hey girlfriend!\nHaven't seen you\nin a while!", 
  "Oh my god, you look gorgeous.",
  "I've had the\nworst day today.", 
  "Why aren't you\nanswering my texts?", 
  "Guess what?", 
  "I love your dress."
};

string brideMoney[] = {
  "I didn't know\nwhat to give you\nfor your wedding,\nso here's some money.", 
  "Here's they money\nI owe you from\nour little deal\nlast night.", 
  "Here's a bit of cash\nto help you get started\non your mortgage.", 
  "Congrats on your wedding\nfrom Mr. Washington."
};

string brideSword[] = {
  "I got you this\nantique sword!", 
  "This is actually\nquite handy around\nthe kitchen.", 
  "Me and Tom wanted to\ngive you this sword\nfor your wedding!", 
  "I got you this.\nIt'll look great\nin your new house!"
};

string brideBowling[] = {
  "I got you\na bowling ball!\nWe should go\nbowling some time.", 
  "Here's a bowling ball\nas a reminder of\nthe pains of pregnancy.", 
  "Bowling is a great way\nto reduce the stress\nof marriage.", 
  "Here's your wedding gift!\nI didn't get a receipt."
};

string brideGun[] = {
  "Don't let him\nboss you around.\nHere, I got you a gun!", 
  "I got this gun\nfrom my dead uncle.\nCongratulations!", 
  "Here's an old\nservice revolver from\nmy boyfriend in jail.", 
  "I got you this gift.\nI hope they allow guns\nin this chapel!"
};

string brideBleach[] = {
  "This bleach will remove\nstains from any\nbodily fluids.", 
  "Here's some bleach\nto keep your laundry clean!", 
  "Congratulations on your wedding!\nYou're gonna need this.", 
  "This bleach will is AMAZING."
};

string feelings0[] = {
  "\nSo, you know how\nBrad and I were engaged?",
  "Well, we got into a fight\nlast night, and I was having\na bad day yesterday,\nyou know?",
  "So I was really\nemotional at the time,\nand I don't know how,\nbut I just started\ncalling him fat.",
  "And he started to\nlook really sad\nand I felt sooo bad\nfor him, you know?",
  "Anyway, then he got out\nhis gun and he killed himself.\nSo now we're not\nengaged anymore."
};

string feelings1[] = {
  "\nDo you think\nMichael's cheating on me?",
  "He comes home late every night\nsmelling of beer and perfume.",
  "I think it's\nthat little harlot\nAshley from work.",
  "Thanks for listening.\nI'm going to kill him\nwhen I get home."
};

string feelings2[] = {
  "Do you think this\npencil skirt looks good\non me?",
  "I got it on sale\nat JCPenny, and now\nI totally regret it.",
  "I couldn't decide on\nfuchsia pink or\npink lavender",
  "I don't know why\nI got this\npastel pink one\nin the end."
};

string feelings3[] = {
  "\nI think Alice\nis onto me and Michael.",
  "Cause Stella told me\nthat Jessica saw us\nat the coffee shop.",
  "And she told Tracy's sister\nMonica about it.",
  "\nAnd you know how\nMonica just can't\nkeep a secret."
};

string feelings4[] = {
  "Did you see that\nludicrous display\nlast night?",
  "The thing about Arsenal\nis they always\ntry to walk it in!"
};

string feelings5[] = {
  "Oh my god.\nI just had the most\nheated debate\nwith my boss",
  "I was trying to\nexplain to him how\ncertain video games\nreinforce negative\ngender stereotypes.",
  "He didn't understand\nthe intersectionality of\ndifferent systems of oppression.",
  "He said I didn't know\nwhat I was talking about\nand he fired me."
};

string feelings6[] = {
  "\nI just saw\nthe cutest shoes\non sale.",
  "It's two sizes\ntoo small, but I think\nI can get them\nto fit with the old\nice trick.",
  "They're going to be\nperfect for those\nbusiness cocktail\nevening casual events."
};

string hoboGreetings[] = {
  "Hey young lady!\nSpare a little change?\nHow about a lot of change?", 
  "Care to donate to the\nhomeless food shelter?", 
  "Spare some change?", 
  "Hey. HEY. HEY!", 
  "* mumbles *", 
  "I need some money.", 
  "Got fi' dollahs?", 
  "Excuse me, I need\nsome money\nfor the bus.", 
  "Spare change?", 
  "I'm hungry!"
};

string hoboGun[] = {
  "These streets are dangerous,\nlittle lady.\nHere, this gun might\ncome in handy.", 
  "I went to rehab\nI don't have any use\nfor this gun anymore.", 
  "I used to be\na young newly wed like you.\nBut then I took\nnine bullets to the kneecap.\nHere's a gun\nfor self-defence.", 
  "I found this gun\nby a body\nin the alleyway."
};

string hoboSword[] = {
  "I found this sword\nin the dumpster.\nDo you want it?", 
  "I made this sword\nfrom some scrap metal\nI want you\nto have it.", 
  "I use this sword\nto defend against\nthose hooligan kids,\nbut you can have it.", 
  "I used to be\na young newly wed like you.\nBut then I took\nmultiple lacerations to the face\nfrom this sword."
};

string hoboBowling[] = {
  "I found this new\nbowling ball in the dumpster.\nCan you believe\nwhat people throw away?", 
  "Someone gave me\nthis bowling ball.\nWhat's a guy\non the street\ngonna do with\na bowling ball?", 
  "This is the bowling ball\nI used before my divorce.", 
  "You look rich.\nDo you enjoy bowling?"
};

string hoboBleach[] = {
  "I found this bleach\nin a portapotty.\nYou look like\nyou can use it.", 
  "I use this bleach\nall the time for\nrecreational purposes.", 
  "I found a gallon of bleach.\nI want you to have it.", 
  "This bleach smells AMAZING."
};

vector< vector<string> > Bridesmaid::allFeelings;
void Bridesmaid::initFeelings() {
  vector<string> temp;
  temp.assign(feelings0, feelings0+sizeof(feelings0)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings1, feelings1+sizeof(feelings1)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings2, feelings2+sizeof(feelings2)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings3, feelings3+sizeof(feelings3)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings4, feelings4+sizeof(feelings4)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings5, feelings5+sizeof(feelings5)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
  temp.assign(feelings6, feelings6+sizeof(feelings6)/sizeof(string));
  allFeelings.push_back(temp);
  temp.clear();
}

Bridesmaid::Bridesmaid(float x, float y, float size, float depth) : Person(x, y, size*.32f, size*.94f, depth) {
  type |= BRIDESMAID;
  renderSize = Vector2f(size, size);
  follower = true;
  
  int randInt = rand()%100;
  if (randInt<30) {
    stash = new Money(Point2f(), 1, rand()%5+rand()%5+rand()%5);
  } else if (randInt >= 30 && randInt < 55) {
    stash = new Sword(Point2f(), 1);
  } else if (randInt >= 55 && randInt < 75) {
    stash = new Bowling(Point2f(), 1);
  } else if (randInt >= 75 && randInt < 80) {
    stash = new Gun(Point2f(), 1);
  } else if (randInt >= 80 && randInt < 85) {
    stash = new Bleach(Point2f(), 1);
  } else {
    stash = NULL;
  }
  
  textureBase = "bm";
  stringstream num;
  num << rand()%2;
  deathAnim = num.str();
  int randomifier = rand()%(sizeof(brideGreetings)/sizeof(string));
  greeting = string(brideGreetings[randomifier]);
  
  randomifier = rand()%7;
  feelings = allFeelings[randomifier];
  currentFeeling = 0;
  randomifier = rand()%4;
  if (stash != NULL) {
    switch (stash->name) {
      case MONEY:
        parting = brideMoney[randomifier];
        break;
      case SWORD:
        parting = brideSword[randomifier];
        break;
      case BOWLING:
        parting = brideBowling[randomifier];
        break;
      case GUN:
        parting = brideGun[randomifier];
        break;
      case BLEACH:
        parting = brideBleach[randomifier];
        break;
        
      default:
        parting = "Here's a gift\nfor your wedding!";
        break;
    }
  }
}

bool Bridesmaid::isSatisfied() {
  if (talking) {
    currentFeeling = int(talkTimer.seconds()/5);
    if (currentFeeling >= int(feelings.size())) {
      talkTimer.reset();
      say(parting);
      talking = false;
      return true;
    }
    *myText->text = feelings[currentFeeling];
  }
  return false;
}

Hobo::Hobo(float x, float y, float size, float depth) : Person(x, y, size*.33f, size*.65f, depth) {
  type |= HOBO;
  renderSize = Vector2f(size, size);
  
  int randInt = rand()%100;
  if (randInt<40) {
    stash = new Gun(Point2f(), 1);
  } else if (randInt >= 40 && randInt < 55) {
    stash = new Sword(Point2f(), 1);
  } else if (randInt >= 55 && randInt < 65) {
    stash = new Bowling(Point2f(), 1);
  } else if (randInt >= 65 && randInt < 70) {
    stash = new Bleach(Point2f(), 1);
  } else {
    stash = NULL;
  }
  
  textureBase = "hobo";
  stringstream num;
  num << rand()%2;
  deathAnim = num.str();
  int randomifier = rand()%(sizeof(hoboGreetings)/sizeof(string));
  greeting = string(hoboGreetings[randomifier]);
  randomifier = rand()%4;
  if (stash != NULL) {
    switch (stash->name) {
      case SWORD:
        parting = hoboSword[randomifier];
        break;
      case BOWLING:
        parting = hoboBowling[randomifier];
        break;
      case GUN:
        parting = hoboGun[randomifier];
        break;
      case BLEACH:
        parting = hoboBleach[randomifier];
        break;
        
      default:
        parting = "I don't got much,\nbut you can have this!";
        break;
    }
  }
}

bool Hobo::isSatisfied() {
  if (money >= 5) {
    say(parting);
    return true;
  }
  return false;
}

