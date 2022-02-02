# chihuahua_adventure

### Origin
This is our final project of **IM1010 Programming Design**. Our professor gave us no restriction, except for we must use C++, for the project, and me and my friends decided to design and implement a game to end our first semester (or say, to celebrate haha). We love chihuahua, a small and cute, but irritable dog. After several discussions, we finally came up our conclusion: we're gonna create a game that could prevent our beloved chihuahua from hungry, and it should be fed in different places so that the game would be more interesting! And that's all the origin of **Chihuahua Adventure**.

### Inspiration
But how to present our ideas? We found a game called ***Duet Game***, and the way to win that game is by passing through as much barriers as possible. We accept some materials of that game but still change most of the parts. We considered that rather than avoid hitting barriers, we could generate foods! That is, We shoulc hit as much barriers as we could to win the game.

### Code Explanation
I would explain some important codes in our main files that keep the program works.
Also, we use `EasyX` library to present our project.

```
struct Randomizer
{
    void chihuahuaFood(int, Form_Food*);
    int cur =clock() ;
    int rand(int);
};
void Randomizer::chihuahuaFood(int level, Form_Food* ptr)
{
    int r = 0;
    for (int i = 0; i < amount_of_food ; i++)
    {
        r = rand(i+1);
        ptr[i].x = 380 + r;
        ptr[i].y = 50 * (i - amount_of_food);
        if (i %xiaojay == 0)
        {
            food[i].value = -1; //小傑
            food[i].radius = 35;
        }
        else if (i % 10 == 0)
        {
            food[i].value = -10; //巧克力
        }
        /*else if (i % 5 == 0)
        {
            food[i].value = 2;  //布丁
        }*/

    }
};
```
