# philo
This project is about the famous philosopher's problem. Around a table sits X philosopher with each one fork. But to eat spaghetti they need to have 2 forks, and if they don't eat fast enough they'll die.
In order to do that, threads are required. Each philosopher will represent a thread, and each fork a mutex. 

I avoided data race in forcing odd threads to sleep time_to_eat ms at the beginning, but some deadlocks might still occur.

The subject though didn't ask to manage slow eating and sleeping time (below 60 ms), but it is still an improvement I can make to this project.

This time they are no bonuses. Getting short on time for the 42's curriculum I decided to go faster, and rush project a little bit more.
