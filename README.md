# chihuahua_adventure

### Origin
This is our final project of **IM1003 Programming Design**. Our professor gave us no restriction, except for we must use C++ for the project. Me and my friends decided to design and implement a game to end our first semester (or say, to celebrate haha).  
We love chihuahua, a small and cute, but irritable dog. After several discussions, we finally came up our conclusion: we're gonna create a game that could prevent our beloved chihuahua from hungry, and it should be fed in different places so that the game would be more interesting! And that's all the origin of **Chihuahua Adventure**.

### Inspiration
But how to present our ideas? We found a game called ***Duet Game***, and the way to win that game is by passing through as much barriers as possible. We accept some materials of that game but still change most of the parts. We considered that rather than avoid hitting barriers, we could generate foods! That is, We should hit as much barriers as we could to win the game.

### Code Explanation
I would explain some important codes in our main files that keep the program works.
Also, we use `EasyX` library to present our project.

#### `Randomizer`
The core of this game. We randomly generate foods and make them drop from the sky. Below is the code.
```
struct Randomizer
{
    void chihuahuaFood(int, Form_Food*);
    int cur = clock();
    int rand(int);
};
void Randomizer::chihuahuaFood(int level, Form_Food* ptr)
{
    int r = 0;
    for (int i = 0; i < amount_of_food; i++)
    {
        r = rand(i + 1);
        ptr[i].x = 380 + r;
        ptr[i].y = 50 * (i - amount_of_food);
        if (i % xiaojay == 0)
        {
            food[i].value = -1;
            food[i].radius = 35;
        }
        else if (i % 10 == 0)
        {
            food[i].value = -10;
        }
        else if (i % 5 == 0)
        {
            food[i].value = 2;  
        }
    }
};
int Randomizer::rand(int leel)
{
    cur = (101 * cur + 10001 ) % 32767;
    return cur % 200 ;
};
```

#### `count_distance`
We use this function to check the distance between chihuahua and foods.
```
int count_distance(int k, Form_Dog item)
{
    return pow(item.y - food[k].y, 2) + pow(item.x - food[k].x, 2);
}
```

#### `collision`
We use this function to check whether chihuahua touches the food or not.
```
bool collision(int k, Form_Dog item)
{
    if (count_distance(k, item) <= pow((item.radius + food[k].radius), 2))
    {
        food[k].x = food[k].y = 10000;
        return 1;
    }
    return 0;
}
```

#### `gainpoint`
We use this function to count the total score the player wins.
```
void gainpoint(int i)
{
    bool leftc = collision(i, left_dog);
    bool rightc = collision(i, right_dog);
   
    if (food[i].visiable)
    {
        score += leftc * food[i].value;
        score += rightc * food[i].value;
        if (score < 0)
            score = 0;
    }
}
```

### Future & ...
We expect to add sounds to this game, also we plan to add more levels to make the game more interesting.  
As you can see, this is a simple game created by freshman students after learning programming for a semester and without complicated logic, but a nice and fun try of creating a game. Hope you like it!  
For further information, feel free to [contact me](mailto:b09705045@ntu.im).
