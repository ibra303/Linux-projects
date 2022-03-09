# Linux-projects
Threads, semaphores, synchronization, DeadLock solving.



The 4 Senior Problem:
4 senior officials work in a government office in 4 cities: Haifa, tzfat, Tiberias and Carmiel. Their secretaries constantly call each other to schedule meetings between officials.
No meetings are scheduled between more than 2 clerks and no secretary can call 2 other secretaries at a time - only one.
ZA, when Haifa calls Tiberias, only Carmiel can call tzfat or vice versa, tzfat to Carmiel.
And when Haifa calls Carmiel, only tzfat can call Tiberias or vice versa, Tiberias to tzfat.
And there is another problem - in tzfat and Haifa the officials are more senior than in Carmiel and Tiberias, therefore, when tzfat and Haifa call each other, Tiberias and Carmiel wait for them and do not schedule meetings until tzfat and Haifa are finished.
On the other hand, if Tiberias calls Carmiel or vice versa, tzfat and Haifa do not have to wait for the end of their talks.


Dining philosophers problem:
Philosophers sit around a round table and dedicate their lives to thinking.
In the center of the table is a bowl of rice.
Between each two philosophers lies a chopstick. 
When a philosopher is hungry, he takes the two sticks on either side and eats.
After finishing his meal he puts the sticks back in place and keeps thinking, and so to no end.
The common resource that philosophers compete for is the chopstick. We would not want to allow two philosophers to simultaneously access some chopstick.

