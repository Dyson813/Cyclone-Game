# Cyclone-Game
Game description: 
I will be doing a version of the Cyclone Arcade game for my game. My version will include a slow-mo button to assist the play butt gradually stops being helpful as you increase in level.


Game rules:
	The left button will be used to give the user a one-time use slow-mo but as they move up in difficulty the amount of time the light is slowed down decreases. When the user gets close or on the exact light they move on to the next level. When they miss the correct light completely then the program beeps, they lose and the game gets reset.




User inputs:
	The left button will be attached to an interrupt function called slow-mo. In that function, it will make the speed of the moving light go slower for 1 second. As the levels increase that time will get shorter. The raw value is ms. The amount of time the slow-mo decreases the speed decreases as you go up every two levels. It starts at 500ms then goes to 400ms then 300ms then 200ms, and 100ms. The right button will be attached to an interrupt function called click. That function will allow the user to click with the light on or near the main light. 
	The switch will be attached to an interrupt function called start. The function will allow the user to start and stop the program. 


Outputs: 
	When the user hits the button on the correct light a short beep plays and all the lights flash signaling the user that they got it and to move onto the next level. When the user gets to the last level with level 10 then they win, a happy song/tone plays, and a function called rainbow firework is called to help signal to the user that they won. 
	When the user doesn't hit the button on the correct light it does and a sad song flashes all the lights red and resets the user back to zero.
	So the user knows what level they are on, the number of lights that are turned on in between levels will indicate which level they are on. 
	Using serial.print I will print out the score. The score corresponds to the level, each level completion is worth 20 points with a total of 200 points to win. When the user fails the score will get reset to zero. 
