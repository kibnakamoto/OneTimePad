"""
By: Taha Canturk (Kibnakamoto)
Github: Kibnakamoto
Date: Jul 17, 2023

OneTimePad licenced under the GNU General Public Licence
"""

# python file for cracking the plaintexts using the data given

from secrets import choice, randbelow
from decimal import Decimal
import time
import re

dot_arts = [
'''
 ________  ________   _______  _________  ___  _____ ______   _______   ________  ________  ________          ________  ________  ________  ________  ___  __    _______   ________     
|\\   __  \\|\\   ___  \\|\\  ___ \\|\\___   ___|\\  \\|\\   _ \\  _   \\|\\  ___ \\ |\\   __  \\|\\   __  \\|\\   ___ \\        |\\   ____\\|\\   __  \\|\\   __  \\|\\   ____\\|\\  \\|\\  \\ |\\  ___ \\ |\\   __  \\    
\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\   __/\\|___ \\  \\_\\ \\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\_|\\ \\       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\/  /|\\ \\   __/|\\ \\  \\|\\  \\   
 \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\_|/__  \\ \\  \\ \\ \\  \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\   ____\\ \\   __  \\ \\  \\ \\\\ \\       \\ \\  \\    \\ \\   _  _\\ \\   __  \\ \\  \\    \\ \\   ___  \\ \\  \\_|/_\\ \\   _  _\\  
  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\  \\ \\  \\ \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\_\\\\ \\       \\ \\  \\____\\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\____\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\\\  \\| 
   \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\  \\ \\__\\ \\ \\__\\ \\__\\    \\ \\__\\ \\_______\\ \\__\\    \\ \\__\\ \\__\\ \\_______\\       \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\__\\\\ _\\ 
    \\|_______|\\|__| \\|__|\\|_______|   \\|__|  \\|__|\\|__|     \\|__|\\|_______|\\|__|     \\|__|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|\\|__| \\|__|\\|_______|\\|__|\\|__|
 ''',

'''
⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠂⠀⠄⠀⠀⠀⠀⠀⠀⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣶⣶⣶⣿⣿⣿⣿⣶⣶⣶⣦⣤⣄⣀⠐⠠⠀⠀⠀⡀⠀⠀⠀⠂⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠠⠀⠂⠁
⠀⠀⠀⡀⠀⠀⢀⠀⠀⠀⢀⠀⠀⠠⠀⠁⠀⠈⠀⠀⣀⣴⣶⣿⣿⣿⠿⠟⠛⠛⠋⢍⣿⣿⠙⠛⠛⠻⠿⣿⣿⣿⣶⣤⣀⠁⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠂⠁⠀⠂⠀⠀⠀⠀
⠀⠀⠁⠀⠀⠈⠀⠀⠁⠀⠀⠀⢀⠀⠀⠀⠀⢀⣴⣾⣿⡿⠟⠋⠁⠀⠀⠀⠀⠀⠀⢀⣿⣿⠀⠀⠀⠀⠀⠀⠈⠙⠻⢿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠁⢀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣴⣿⣿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣶⣀⠀⠀⠀⠐⠀⠀⠀⠀⠀⠐⠀⠀⠀⠂⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⢠⣴⣿⣿⡟⠁⠀⠀⠀⠀⠀⠈⠀⠀⠐⠀⠀⠀⢠⣿⣿⠀⠀⠀⠀⠀⠈⠀⠀⠁⠀⠀⠀⠀⢹⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⡀⠀
⠃⠀⠀⠘⠀⠀⠘⠀⠀⠀⠃⠀⢀⣾⣿⡿⠋⠀⠀⠀⠀⠀⠃⠀⠀⠀⠃⠀⠀⠃⠀⠘⣿⣿⠘⠀⠀⠀⠃⠀⠀⠘⠀⠀⠀⠀⠀⠀⠙⢿⣿⣷⡀⠀⠃⠀⠘⠀⠀⠀⠃⠀⠀⠁⠀
⡀⠌⠀⠀⡀⠀⠀⡀⠀⠀⠀⢀⣾⣿⡟⠁⢀⠀⠀⠀⠀⠀⢀⠀⠈⠀⠀⠈⠀⠀⠀⢐⣿⣿⠀⠀⠀⠀⡀⠈⠀⠀⠀⠁⢀⠈⠀⠀⠀⠐⢻⣿⣿⡀⠀⠀⠀⡀⠈⠀⡀⠀⠀⡀⠀
⠀⠀⠠⠀⠀⠠⠀⠀⠀⠄⢀⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠄⠀⠀⠄⠀⠀⠠⠀⡀⠠⢀⣿⣿⠀⠀⠀⠀⢀⠀⠄⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⡀⠐⠀⠀⠀⠀⠀⠠⠀⠀⠀
⠀⠂⠀⠀⠀⠠⠀⠂⠀⠀⣼⣿⡿⠐⠀⠀⠀⠀⠄⠂⠀⠀⠀⠂⠀⠀⠂⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠂⠀⠀⠐⠀⠀⠀⠀⠐⠀⠀⠀⠀⠀⢻⣿⣧⠀⠀⠂⠀⠐⠀⠀⠀⠂⠀
⠂⠀⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⢇⠀⠀⠐⠀⠀⠀⠀⠀⠀⠐⠀⠈⠀⠀⠈⠀⡀⠈⠐⣿⣿⠀⠀⠀⠁⠀⠀⠀⠀⠀⠁⠀⠁⠀⡀⠈⠀⠐⠀⠘⣿⣿⡆⠀⠀⠀⠀⠂⠀⠀⡀⠀
⠀⠀⠈⠀⠀⠈⠀⡀⠀⢸⣿⣿⠀⠀⠀⠄⠀⠠⠀⠀⠠⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠀⠀⠀⠀⠀⠠⠀⠀⠠⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⢿⣿⣧⠀⠀⠐⠀⠀⠠⢀⠀⠀
⠐⠀⠀⠂⠀⠀⠄⠀⠀⣿⣿⣿⣶⣶⣶⣾⣶⣶⣶⣶⣶⣶⣶⣶⣶⣾⣷⣶⣶⣶⣶⣶⣿⣿⣶⣶⣾⣶⣶⣶⣶⣾⣶⣶⣶⣶⣶⣾⣶⣶⣶⣶⣶⣾⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠄⠁⠀⠀⠀⠀⠀⠀⢹⣿⣟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⣿⣿⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⢻⣿⣿⡀⠀⠀⠀⠀⠀⠀⡀⠀
⠀⠀⡀⠀⠀⠐⠀⠀⠀⢸⣿⣿⠀⠀⠀⡀⠀⠀⡀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⢀⠈⣿⣿⠀⠀⠀⠀⠀⠀⡀⠀⠀⡀⠀⢀⠀⠀⠀⠀⠀⠀⠀⣾⣿⡏⠁⠀⢀⠀⠁⢀⠀⠀⠀
⠄⠂⠀⠀⠄⠀⠀⠄⠀⠘⣿⣿⡆⠀⠀⠀⠠⠀⠀⠀⠀⠀⠠⠀⠀⠀⠄⠀⠠⠀⠀⠈⣿⣿⠠⠀⠀⠀⠄⠀⠀⠠⠀⠀⠠⠀⠀⠀⠀⠀⠠⠀⢠⣿⣿⢇⠀⠀⠀⠀⠄⠀⠀⠄⠀
⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⡀⠀⠀⠀⠀⠀⢀⠀⠂⠀⠀⠂⠀⠀⠐⠀⠀⠐⠠⣿⣿⠀⠀⠀⠀⠀⠂⠀⠀⠀⠂⠀⠀⢀⠀⠀⠂⠀⠀⣾⣿⡟⠀⠀⡀⠂⠀⠀⠀⠀⠀⠀
⠀⠁⡀⠀⠁⢀⠀⠁⠀⠀⠈⢿⣿⣧⠀⠀⠈⠀⠀⠀⠀⡀⠈⠀⡀⠀⠁⢀⠀⠀⢀⠠⣿⣿⠀⠀⢀⠀⠁⠀⡀⠈⠀⡀⠈⢀⠀⠀⠀⠀⠀⣽⣿⡿⠁⠀⠀⢀⠀⠀⠁⠀⠀⠁⠀
⠁⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣷⡀⠀⡀⠀⡄⠀⠀⠀⠀⠀⠀⡄⠀⠀⠁⠀⢠⣿⣿⠀⠀⠀⠀⠀⡀⠀⠀⠀⡀⢠⠀⠀⠀⠀⢀⣽⣿⣿⠁⠀⡀⠀⡄⠀⠀⡄⠀⢠⠀⠀
⡀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢿⣿⣿⡆⠁⠀⠀⠀⠆⢀⠀⠰⠀⠀⠀⠀⡀⠰⠀⣿⣿⠀⠀⠰⠀⡀⠁⠀⠀⠀⠁⠀⠀⠀⠀⢀⣾⣿⡿⠃⠀⠀⠁⠀⠀⠀⠀⡀⠰⠀⠀⠀
⠀⠀⠠⠀⠂⠀⠐⠀⠤⠀⠀⠠⠀⠀⠹⣿⣿⣦⡀⠀⠀⠀⠀⠀⠄⠀⠂⠀⠀⠀⠀⢈⣿⣿⠀⠀⠀⠀⠀⠀⡀⠐⠀⠀⠀⠀⢈⣴⣿⣿⠟⠁⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀
⠄⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠠⣿⣿⠀⠀⠈⠀⢀⠀⠀⠀⠀⠀⣠⣴⣿⣿⠟⠁⠀⠀⠀⠀⠀⠈⠀⠀⠀⢀⠀⠀⠀⡀⠀
⠀⠐⠀⠀⠀⠀⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠠⣿⣿⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⡿⠛⠁⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀
⠄⠀⠀⠠⠀⠀⠠⠀⠀⠀⠄⠀⠐⠈⠀⠠⠀⠀⠀⠀⠈⠙⠻⢿⣿⣿⣷⣶⣦⣤⣤⣴⣿⣿⣤⣤⣴⣶⣾⣿⣿⡿⠿⠛⠁⠀⠀⠀⠀⠀⠄⠀⠀⠀⠄⠀⠀⠂⠀⠀⠄⠀⠀⠂⠀
⠀⡐⠀⠀⠀⠀⠀⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠐⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠻⠿⠿⠿⠿⠿⠿⠿⠿⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠁⢀⠀⠀⠁⠀⠈⠀⠀⠀⠈⠀⠀⠈⠀⠀⠁⠀⠀⠈⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠁⠀⠀⠁⠀⠀⠈⠀⠀⠈⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠀⠀⠁⠀
''',
'''
⣶⣴⣶⣦⣶⣴⣦⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣶⡀⠀⠀⠀⣴⡆⠀⠀⠀⠀⠀⠀⠀⣠⡤⠶⠦⣤⣀⠀⠀⠀⠀⠀⠀⢶⣦⠀⠀⠀⠀⣠⣶⠆
⠀⠀⠀⠀⢠⣾⠟⠁⠀⠀⠀⠀⠀⢰⣶⣶⣶⣶⣶⣶⡆⠀⠀⠀⠀⠀⠀⠹⣿⡄⢀⣾⠟⠀⠀⠀⠀⠀⠀⢠⠞⠁⠀⢹⠁⠀⠙⢷⡀⠀⠀⠀⠀⠈⢿⣧⡀⠀⣸⣿⠃⠀
⠀⠀⢀⣴⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠸⣿⣾⡏⠀⠀⠀⠀⠀⠀⢠⣿⣤⣀⣀⣸⣅⣀⣀⡌⡇⠀⠀⠀⠀⠀⠈⢿⣷⣰⣿⠇⠀⠀
⠀⢀⣼⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⣀⣀⢀⡀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡿⢿⣆⠀⠀⠀⠀⠀⠀⠘⣯⠉⠉⠉⢹⠍⠉⠉⢁⡇⠀⠀⠀⠀⠀⠀⠈⢿⣿⠃⠀⠀⠀
⣠⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⠿⠿⠿⠿⠿⠇⠀⠀⠀⠀⠀⠀⣰⡿⠁⠈⢿⣧⠀⠀⠀⠀⠀⠀⠘⢧⣀⠀⢸⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀
⠻⠛⠻⠛⠟⠻⠛⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠛⠁⠀⠀⠀⠻⠛⠀⠀⠀⠀⠀⠀⠀⠉⠛⠓⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⠀⠀⠀⠀
''',
'''
 /$$$$$$                   /$$$$$$$$ /$$                         /$$$$$$$                 /$$       /$$$$$$$$                     /$$           /$$   /$$
 /$$__  $$                 |__  $$__/|__/                        | $$__  $$               | $$      | $$_____/                    | $$          |__/  | $$
| $$  \\ $$ /$$$$$$$   /$$$$$$ | $$    /$$ /$$$$$$/$$$$   /$$$$$$ | $$  \\ $$ /$$$$$$   /$$$$$$$      | $$       /$$   /$$  /$$$$$$ | $$  /$$$$$$  /$$ /$$$$$$
| $$  | $$| $$__  $$ /$$__  $$| $$   | $$| $$_  $$_  $$ /$$__  $$| $$$$$$$/|____  $$ /$$__  $$      | $$$$$   |  $$ /$$/ /$$__  $$| $$ /$$__  $$| $$|_  $$_/
| $$  | $$| $$  \\ $$| $$$$$$$$| $$   | $$| $$ \\ $$ \\ $$| $$$$$$$$| $$____/  /$$$$$$$| $$  | $$      | $$__/    \\  $$$$/ | $$  \\ $$| $$| $$  \\ $$| $$  | $$
| $$  | $$| $$  | $$| $$_____/| $$   | $$| $$ | $$ | $$| $$_____/| $$      /$$__  $$| $$  | $$      | $$        >$$  $$ | $$  | $$| $$| $$  | $$| $$  | $$ /$$
|  $$$$$$/| $$  | $$|  $$$$$$$| $$   | $$| $$ | $$ | $$|  $$$$$$$| $$     |  $$$$$$$|  $$$$$$$      | $$$$$$$$ /$$/\\  $$| $$$$$$$/| $$|  $$$$$$/| $$  |  $$$$/
 \\______/ |__/  |__/ \\_______/|__/   |__/|__/ |__/ |__/ \\_______/|__/      \\_______/ \\_______/      |________/|__/  \\__/| $$____/ |__/ \\______/ |__/   \\___/
                                                                                                                        | $$
                                                                                                                        | $$
                                                                                                                        |__/
 /$$$$$$$                  /$$   /$$ /$$ /$$                           /$$                                           /$$
| $$__  $$                | $$  /$$/|__/| $$                          | $$                                          | $$
| $$  \\ $$ /$$   /$$      | $$ /$$/  /$$| $$$$$$$  /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$$$$$    /$$$$$$
| $$$$$$$ | $$  | $$      | $$$$$/  | $$| $$__  $$| $$__  $$ |____  $$| $$  /$$/ |____  $$| $$_  $$_  $$ /$$__  $$|_  $$_/   /$$__  $$
| $$__  $$| $$  | $$      | $$  $$  | $$| $$  \\ $$| $$  \\ $$  /$$$$$$$| $$$$$$/   /$$$$$$$| $$ \\ $$ \\ $$| $$  \\ $$  | $$    | $$  \\ $$
| $$  \\ $$| $$  | $$      | $$\\  $$ | $$| $$  | $$| $$  | $$ /$$__  $$| $$_  $$  /$$__  $$| $$ | $$ | $$| $$  | $$  | $$ /$$| $$  | $$
| $$$$$$$/|  $$$$$$$      | $$ \\  $$| $$| $$$$$$$/| $$  | $$|  $$$$$$$| $$ \\  $$|  $$$$$$$| $$ | $$ | $$|  $$$$$$/  |  $$$$/|  $$$$$$/
|_______/  \\____  $$      |__/  \\__/|__/|_______/ |__/  |__/ \\_______/|__/  \\__/ \\_______/|__/ |__/ |__/ \\______/    \\___/   \\______/
           /$$  | $$
          |  $$$$$$/
           \\______/
''',
'''     


    ...   :::.    :::..,:::::::::::::::::::::.        :  .,::::::::::::::::. :::.   :::::::-.      .,::::::    .,::      .:::::::::::. :::         ...     :::::::::::::::
 .;;;;;;;.`;;;;,  `;;;;;;;\'\'\'\';;;;;;;;\'\'\'\';;;;;,.    ;;; ;;;;\'\'\'\' `;;;```.;;;;;`;;   ;;,   `\';,    ;;;;\'\'\'\'    `;;;,  .,;;  `;;;```.;;;;;;      .;;;;;;;.  ;;;;;;;;;;;\'\'\'\'
,[[     \\[[,[[[[[. \'[[ [[cccc      [[     [[[[[[[, ,[[[[, [[cccc   `]]nnn]]\',[[ \'[[, \`[[     [[     [[cccc       \'[[,,[[\'    `]]nnn]]\' [[[     ,[[     \\[[,[[[     [[     
$$$,     $$$$$$ "Y$c$$ $$""""      $$     $$$$$$$$$$$"$$$ $$""""    $$$""  c$$$cc$$$c $$,    $$     $$""""        Y$$$P       $$$""    $$\'     $$$,     $$$$$$     $$     
"888,_ _,88P888    Y88 888oo,__    88,    888888 Y88" 888o888oo,__  888o    888   888,888_,o8P\'     888oo,__    oP"``"Yo,     888o    o88oo,.__"888,_ _,88P888     88,    
  "YMMMMMP" MMM     YM """"YUMMM   MMM    MMMMMM  M\'  "MMM""""YUMMM YMMMb   YMM   ""` MMMMP"`       """"YUMMM,m"       "Mm,   YMMMb   """"YUMMM  "YMMMMMP" MMM     MMM    

'''
]

colors = ["31", "32", "34", "36", "37", "91", "92",  "38;2;176;29;2", "38;2;140;0;0", "38;2;9;4;140"] # ansii escape codes

print(f"\033[1;{choice(colors)}m{choice(dot_arts)}\033[0m")

def onetimepad(x:str,y:str) -> str:
    ret = ""
    for i in range(len(x)):
        ret += chr(ord(x[i]) ^ ord(y[i]))
    return ret

# str to hex
def hx(x):
    ret = ""
    for i in x:
        ret += hex(ord(i))[2:].zfill(2)
    return ret

def unieqe_len(lst):
    s = set(lst)
    sizes = [0]*len(s)
    i=0
    for e in s:
        for j in lst:
            if j == e:
                sizes[i]+=1
        i+=1
    return sizes

# seperate every ith value
def sep(string, i=2) -> list:
    lst = []
    for j in range(0, len(string), 2):
        lst.append(string[j:j+2])
    return lst

def warning(msg):
    print("\033[95;1;5mwarning: \033[0m\033[1;95;23m", msg, "\033[0m")

def message(msg):
    print("\033[95;3m[msg] \033[0m\033[95;23m", msg, "\033[0m")

def add(string, i):
    return string[:i] + ' ' + string[i:]

def rm(string, i):
    return string[:i] + string[i+1:]


# set general data variables
with open("out/data.txt", "r") as f:
    data_txt = f.readlines()
    length = int(data_txt[0].replace("len: ", ""))
    m1m2_tmp = data_txt[1].replace("m1m2: ", "")[:-1]
    ct1_tmp = data_txt[2].replace("ct1: ", "")[:-1]
    ct2_tmp = data_txt[3].replace("ct2: ", "")[:-1]
    m1m2 = bytes(bytearray.fromhex(m1m2_tmp))
    ct1 = bytes(bytearray.fromhex(ct1_tmp))
    ct2 = bytes(bytearray.fromhex(ct2_tmp))

pt1 = ""
pt2 = ""
print("\033[1;32mlength of message:\t\033[0m", length)
print("\n\x1b[1;31mciphertext 1(ct1):\t\x1b[0m\033[37;1m ", ct1_tmp, "\033[0m")
print("\x1b[1;31mciphertext 2 (ct2):\t\x1b[0m\033[37;1m ", ct2_tmp, "\033[0m")
print("\n\x1b[1;31mm1 xor m2 (m1m2):\t\x1b[0m\033[37;1m ", m1m2_tmp, "\033[0m")
print()

inc = 100//length

# Data format: index: {x,y} where x xor y = m1m2. X and Y = can be plaintexts and ciphertexts (with same key). results in the same OneTimePad Exploit
pt1_progress_bar = ""
# first use bigrams
with open("out/bigrams.txt", "r") as f:
    # calculate possible plaintext using bigrams
    bigrams_txt = f.readlines()
    bigrams_len = int(bigrams_txt[0].replace("bigram count: ", ""))
    bigrams_txt.remove(bigrams_txt[0]) # remove first index (len)
    bigram_indexes = []
    bigrams_p1 = []
    bigrams_p2 = []
    all_lines = ""

    # set bigrams and bigram indexes
    for line in bigrams_txt:
        index = int(line.partition(":")[0])
        start = line.index("{")
        end = line.index("}")
        first = line[start+1:start+3]
        second = line[end-2:end]
        xored = onetimepad(first, second)

        if hx(xored) != m1m2_tmp[index*2:index*2+4]:
            warning("found a NON-matching m1m2 bigram ciphertext")
            message(f"{first} xor {second} !=  {m1m2_tmp[index*2:index*2+4]}")
            message(hx(onetimepad(first, second)) + " != " + m1m2_tmp[index*2:index*2+4])
            bigrams_txt.remove(line)
            continue
        bigram_indexes.append(index)
        bigrams_p1.append(first)
        bigrams_p2.append(second)
        all_lines += line + "\n"
    
    with open(f"out/bigram.py", "w") as file:
        file.write('''def onetimepad(x:str,y:str) -> str:
    ret = ""
    for i in range(len(x)):
        ret += chr(ord(x[i]) ^ ord(y[i]))
    return ret\n''')
        file.write('''\ndef hx(x):
    ret = []
    for i in x:
        ret.append(hex(ord(i))[2:].zfill(2))
    return ret\n''')
        file.write(f"\nb1 = {bigrams_p1}\nb2 = {bigrams_p2}\nm1m2={sep(m1m2_tmp)}\nwith open(\"out/bigram_out.txt\", \"w\") as f:\n")
        sizes = unieqe_len(bigram_indexes)
        num = sizes[0]
        prev_num = 0

        for i in range(len(sizes)):
            file.write("    "*(i+1) + f"for i{i} in range({prev_num}, {num}):\n")
            if i != len(sizes)-1:
                num += sizes[i+1]
            prev_num += sizes[i]
        tabs = len(sizes)*"    " + "    "
        # file.write(f"{tabs}tmp = ")
        # for i in range(len(sizes)-1):
        #     file.write(f"b1[i{i}]")
        #     if i < len(sizes)-2:
        #         file.write(" + ")
        # file.write("+ \" : \" + ")

        # for i in range(len(sizes)-1):
        #     file.write(f"b2[i{i}]")
        #     if i < len(sizes)-2:
        #         file.write(" + ")
        # file.write(f"\n{tabs}f.write(tmp + \"\\n\")")
        file.write(f"{tabs}string = list(\" \"*{length})")
        file.write(f"\n{tabs}string2 = list(\" \"*{length})")
        for i in range(len(sizes)-1):
            file.write(f"\n{tabs}ind = {list(set(bigram_indexes))[i]}")
            file.write(f"\n{tabs}string[ind] = b1[i{i}][0]")
            file.write(f"\n{tabs}string[ind+1] = b1[i{i}][1]")
            file.write(f"\n{tabs}string2[ind] = b2[i{i}][0]")
            file.write(f"\n{tabs}string2[ind+1] = b2[i{i}][1]")
        file.write(f"\n{tabs}for ind in range({length}):")
        file.write(f"\n{tabs}    if hx(onetimepad(string, string2))[ind] != m1m2[ind]:") # if index doesn't match
        file.write(f"\n{tabs}        for i in range(256):") 
        file.write(f"\n{tabs}            if 32 ^ i == int(m1m2[ind], 16):") # 32 is ' '
        if randbelow(2) == 1: # flip coin to see who should get space
            file.write(f"\n{tabs}                string[ind] = \' \'")
            file.write(f"\n{tabs}                string2[ind] = chr(i)")
            file.write(f"\n{tabs}                break")
        else:
            file.write(f"\n{tabs}                string2[ind] = \' \'")
            file.write(f"\n{tabs}                string[ind] = chr(i)")
            file.write(f"\n{tabs}                break")
        file.write(f"\n{tabs}strings = \"\\\"\" + \'\'.join(i for i in string) + \"\\\" : \\\"\" + \'\'.join(i for i in string2) + \"\\\"\"")
        file.write(f"\n{tabs}print(strings)")
        file.write(f"\n{tabs}f.write(strings + \"\\n\")")
        file.write(f"\n{tabs}print(hx(onetimepad(string, string2)), \" : \" , m1m2)")
        file.write(f"\n{tabs}exit()")
    exec(open("out/bigram.py").read()) # run the file

    with open("out/bigram_out.txt", "r+") as f:
        # check the indexes and correct them
        lines = f.readlines()
        for line in lines:
            part = line.partition(" : ")
            msg1 = part[0]
            msg2 = part[2]

            
            # all found indexes are correct, now fill the wrong ones. compare 

    # to use the bigrams, ask the user for their own data. For context of the message, then try to generate sentences using that. Then compare the data. if any data matches, use it

