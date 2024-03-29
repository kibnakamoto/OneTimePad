from secrets import choice

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
