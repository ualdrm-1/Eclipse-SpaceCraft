#include "menu.h"
#include "game.h"
#include "classTexts.h"
#include <sstream>
#include <list>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);
// Функция перехода к игре
int GamеStart();
// Функция списка рекордов
void List();
void About_Game();
String myname();
void writeToTextFile(string name, int score, string file);
void sort_file(const string& filename);

bool operator <(const playerscoring& lhs, const playerscoring& rhs) {
    return lhs.score > rhs.score;
}

int main()
{
    // Создаём окно windows
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"ECLIPSE SPACECRAFT", Style::Fullscreen);
    SoundBuffer menuup, menudown, menuenter, menuesc;
    menuup.loadFromFile("sound/menuUP.wav");
    menudown.loadFromFile("sound/menuDOWN.wav");
    menuenter.loadFromFile("sound/enter.wav");
    menuesc.loadFromFile("sound/esc.wav");
    Sound up(menuup), down(menudown), enter(menuenter), escape(menuesc);

    Music menu, what;
    menu.openFromFile("music/fone.wav");
    what.openFromFile("music/what.wav");
    menu.play();
   what.play();
    menu.setVolume(10);
    what.setVolume(100);
    menu.setLoop(true);

    //отключаем видимость курсора
    window.setMouseCursorVisible(false);

    // получаем текущий размер экрана
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // Устанавливаем фон
    // Загружаем в прямоугольник текстуру с изображением
    Texture texture_window;
    if (!texture_window.loadFromFile("image/space_menu.png")) return 4;
    Sprite background;
    background.setTexture(texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("font/GTA.ttf")) return 5;
    Text Titul, name;
    Titul.setFont(font);
    name.setFont(font);
    // Текст с названием игры
    InitText(Titul, 480, 50, L"ECLIPSE SPACECRAFT", 150, Color(186, 255, 250), 3);

    InitText(name, 1280, 980, L"Mandzhiev Aldar I924B", 80, Color(186, 255, 250), 3);

    // Название пунктов меню
    String name_menu[]{ L"НАЧАТЬ",L"СПИСОК РЕКОРДОВ", L"ОБ ИГРЕ",L"ВЫЙТИ" };
    string nameofplayer;
    int playerscore = 0;

    // Объект игровое меню
    game::GameMenu mymenu(window, 950, 350, 4, name_menu, 100, 120);
    // Установка цвета элементов пунктов меню
    mymenu.setColorTextMenu(Color(161, 255, 250), Color(252, 102, 0), Color::Black);
    // выравнивание по центру пунктов меню 
    mymenu.AlignMenu(2);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                // События выбра пунктов меню
                // нажати на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); up.play(); }
                // нажати на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); down.play(); }
                // нажати на клавиатуре клавиши Enter
                if (event.key.code == Keyboard::Return)
                {
                    enter.play();
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:
                        nameofplayer = myname();
                        if (nameofplayer.length()>1) {
                        playerscore = GamеStart();
                    }; break;
                    case 1:List();     break;
                    case 2:About_Game();  break;
                    case 3:window.close(); break;
                    }
                }
                if (event.key.code == Keyboard::Escape) { escape.play(); }
                if (event.key.code == Keyboard::Y) { what.stop(); }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(Titul);
        window.draw(name);
        mymenu.draw();
        window.display();
    }
    writeToTextFile(nameofplayer, playerscore, "fileofscores");
    sort_file("fileofscores.txt");
    return 0;
}

// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font,
    Color menu_text_color, int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}

void About_Game()
{
    RenderWindow About(VideoMode::getDesktopMode(), L"ABOUT", Style::Fullscreen);
    RectangleShape background_ab(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height)), set1(Vector2f(420, 290));

    Texture texture_ab;

    Font font;
    if (!font.loadFromFile("font/GTA.ttf")) exit(6);
    Text titul, buttons, wtext, atext, stext, dtext, spacetext, left, up, down, right, wtext1, atext1, stext1, dtext1, esctext;
    titul.setFont(font); buttons.setFont(font), wtext.setFont(font), atext.setFont(font), stext.setFont(font), dtext.setFont(font), spacetext.setFont(font), esctext.setFont(font);
    left.setFont(font); up.setFont(font); down.setFont(font); right.setFont(font), wtext1.setFont(font), atext1.setFont(font), stext1.setFont(font), dtext1.setFont(font);

    ImageText w("image/w.png", 150, 220, false), a("image/a.png", 150, 390, false), s("image/s.png", 150, 560, false), d("image/d.png", 150, 730, false), space("image/space.png", 50, 900, false),
        esc("image/escape.png", 1100, 900, false), u("image/up.png", 1100, 220, false), downn("image/down.png", 1100, 390, false), l("image/left.png", 1100, 560, false), r("image/right.png", 1100, 730, false);

    InitText(titul, 630, 5, L"УПРАВЛЕНИЕ", 150, Color(186, 255, 250),3);

    InitText(wtext, 380, 240, L"ДВИЖЕНИЕ ВВЕРХ", 75, Color(161, 255, 250),3); InitText(wtext1, 1340, 240, L"ДВИЖЕНИЕ ВВЕРХ", 75, Color(161, 255, 250),3);
    InitText(atext, 380, 405, L"ДВИЖЕНИЕ ВЛЕВО", 75, Color(186, 255, 250),3); InitText(atext1, 1340, 405, L"ДВИЖЕНИЕ ВНИЗ", 75, Color(186, 255, 250),3);
    InitText(stext, 380, 570, L"ДВИЖЕНИЕ ВНИЗ", 75, Color(186, 255, 250),3); InitText(stext1, 1340, 570, L"ДВИЖЕНИЕ ВЛЕВО", 75, Color(186, 255, 250),3);
    InitText(dtext, 380, 735, L"ДВИЖЕНИЕ ВПРАВО", 75, Color(186, 255, 250),3); InitText(dtext1, 1340, 735, L"ДВИЖЕНИЕ ВПРАВО", 75, Color(186, 255, 250),3);
    InitText(spacetext, 470, 920, L"ВЫСТРЕЛ", 90, Color(186, 255, 250),3); InitText(esctext, 1340, 900, L"НАЗАД", 90, Color(186, 255, 250),3);

    if (!texture_ab.loadFromFile("image/space_menu3.png")) exit(3);
    background_ab.setTexture(&texture_ab);
    while (About.isOpen())
    {
        Event event_play;
        while (About.pollEvent(event_play))
        {
            if (event_play.type == Event::Closed) About.close();
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.draw(w.sprite); About.draw(a.sprite); About.draw(s.sprite); About.draw(d.sprite);
        About.draw(u.sprite); About.draw(l.sprite); About.draw(r.sprite); About.draw(downn.sprite);
        About.draw(space.sprite); About.draw(esc.sprite);
        About.draw(titul);
        About.draw(wtext); About.draw(stext); About.draw(atext); About.draw(dtext), About.draw(spacetext);
        About.draw(wtext1); About.draw(stext1); About.draw(atext1); About.draw(dtext1); About.draw(esctext);
        About.display();
    }
}

// Функция списка рекордов
void List()
{
    RenderWindow List(VideoMode::getDesktopMode(), L"SETTINGS", Style::Fullscreen);

    RectangleShape background_opt(Vector2f(1920, 1080));
    Texture texture_opt;
    if (!texture_opt.loadFromFile("image/space_menu2.png")) exit(2);
    background_opt.setTexture(&texture_opt);

    Font font;
    if (!font.loadFromFile("font/GTA.ttf")) exit(6);
    Text titul, isitname;
    titul.setFont(font), isitname.setFont(font);

    ImageText scorebar("image/tablitsa.png", 310, 200, true);

    InitText(titul, 700, 0, L"ЗАЛ ПОЧЕТА", 150, Color(186, 255, 250), 3);
    InitText(isitname, 760, 170, L"ИМЯ+СЧЕТ", 125, Color(186, 255, 250), 3);

    Text text("", font, 100);
    text.setFillColor(Color(0, 0, 0));
    
    ifstream file("fileofscores.txt");
    List.draw(background_opt);
    List.draw(titul);
    List.draw(isitname);
    List.draw(scorebar.sprite);
    int count = 0;
    std::string line;
    while (getline(file, line) && count < 10) {
        string name;
        int score;
        istringstream iss(line);
        if (!(iss >> name >> score)) {
            cerr << "invalid" << line << endl;
            continue;
        }
        if (score != 0) {
            text.setString(name + " " + to_string(score));
            text.setPosition(500, 240+count * 74);
            List.draw(text);
            count++;
        }
    }
    List.display();
    file.close();
    while (List.isOpen())
    {
        Event event_opt;
        while (List.pollEvent(event_opt))
        {
            if (event_opt.type == Event::Closed) List.close();
            if (event_opt.type == Event::KeyPressed)
            {
                if (event_opt.key.code == Keyboard::Escape) List.close();
            }
        }
    }
    file.close();
}
// Функция перехода к игре
int GamеStart()
{
    srand(time(0));
    RenderWindow Play(VideoMode::getDesktopMode(), L"START", Style::Fullscreen);

    float moveframe = 0, moveframedestroy = 0, bonusframe1 = 0, bonusframe2 = 0, bonusframe3 = 0, bulletframe = 0, bossframe = 0;

    RectangleShape background_play(Vector2f(1920, 1080));

    SoundBuffer boomsound, babah, bonusbuf, hitbuf;
    boomsound.loadFromFile("sound/boom.wav"); babah.loadFromFile("sound/babah.wav"), bonusbuf.loadFromFile("sound/bonus.wav"), hitbuf.loadFromFile("sound/hit.wav");
    Sound boom(boomsound), bbh(babah), Bonus(bonusbuf), hits(hitbuf);
    boom.setVolume(30); bbh.setVolume(70); Bonus.setVolume(70);

    int gametime = 0;
    Clock clock;
    Clock gametimeclock;

    ship player(300, 500, 145, 77, "image/ship6.png", "ship");

    boss Boss(1500, 300, 520, 466, "image/boss.png", "BOSS");

    Font font; font.loadFromFile("font/GTA.ttf");
    Text text("", font, 75);
    text.setFillColor(Color::Black); text.setStyle(Text::Bold);
    Text textscore("", font, 100);
    textscore.setFillColor(Color(161, 255, 250)); textscore.setStyle(Text::Bold);

    Text plscore;
    plscore.setFont(font);
    InitText(plscore, 50, 0, L"СЧЕТ:", 100, Color(186, 255, 250), 3);

    ImageText pausing("image/pausefon.png", 538, 330, true), undertablo("image/undertablo.png", -5, 970,true), timebar("image/timebar.png", 720, 0,true), win("image/win.png", 538, 330,true), lose("image/lose.png", 538,330,true);
    pausing.sprite.setColor(Color(255, 255, 255, 0));
    win.sprite.setColor(Color(255, 255, 255, 0));
    lose.sprite.setColor(Color(255, 255, 255, 0));

    Texture texture_play;

    if (!texture_play.loadFromFile("image/space_menu1.png")) exit(1);
    background_play.setTexture(&texture_play);

    bool pr = false, pl = false, pause = false;

    list <object*> objects, ob, bonuslist;
    list <object*>::iterator it, ot;

    Image im;
    im.loadFromFile("image/exp.png");
    im.createMaskFromColor(Color(255, 255, 255));
    Texture te;
    te.loadFromImage(im);

    for (int i = 0; i < 100; i++) {
        int x1 = 1920 + rand() % 10000;
        int x2 = rand() % 1080;
        objects.push_back(new meteor(x1, x2, 130, 131, "image/meteor.png", "asteroid"));
    }
    for (int i = 0; i < 6; i++) {
        int x1 = 1920 + rand() % 10000;
        int x2 = rand() % 1080;
        bonuslist.push_back(new bonus(x1, x2, 50, 50, "image/speed.png", "bonus1"));
    }
    for (int i = 0; i < 6; i++) {
        int x1 = 1920 + rand() % 10000;
        int x2 = rand() % 1080;
        bonuslist.push_back(new bonus(x1, x2, 50, 50, "image/speed.png", "bonus2"));
    }
    for (int i = 0; i < 10; i++) {
        int x1 = 1920 + rand() % 10000;
        int x2 = rand() % 1080;
        bonuslist.push_back(new bonus(x1, x2, 50, 50, "image/speed.png", "bonus3"));
    }

    while (Play.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if (!pause) { gametime = gametimeclock.getElapsedTime().asSeconds(); }
        clock.restart();
        time = time / 800;

        Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.type == Event::KeyPressed) {
                if (event_play.key.code == Keyboard::P) {
                    if (!pause) {
                        pause = true;
                        pausing.sprite.setColor(Color(255, 255, 255, 255));
                    }
                    else if(event_play.key.code == Keyboard::P && pause) {
                        pause = false;
                        pausing.sprite.setColor(Color(255, 255, 255, 0));
                    }
                }
                else if (event_play.key.code == Keyboard::Escape) {
                    pausing.sprite.setColor(Color(255, 255, 255, 0));
                    Play.close();
                }
            }
        }
        if (!pause) {
            if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
                moveframe += 0.01 * time;
                if (moveframe > 4) moveframe -= 4;
                player.sprite.setTextureRect(IntRect(150 * int(moveframe), 0, 150, 79));
            }

            if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
                moveframe += 0.01 * time;
                if (moveframe > 4) moveframe -= 4;
                player.sprite.setTextureRect(IntRect(150 * int(moveframe), 0, 150, 79));
            }

            if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
                moveframe += 0.01 * time;
                if (moveframe > 4) moveframe -= 4;
                player.sprite.setTextureRect(IntRect(150 * int(moveframe), 0, 150, 79));
            }

            if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
                moveframe += 0.01 * time;
                if (moveframe > 4) moveframe -= 4;
                player.sprite.setTextureRect(IntRect(150 * int(moveframe), 0, 150, 79));
            }

            if (pr == false) {
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    ob.push_back(new bullet(player.x, player.y, 60, 16, "image/shots.png", player.dir, "bullet"));
                    boom.play();
                    pr = true;
                }
            }
            else if ((event_play.type == Event::KeyReleased) && (event_play.key.code == Keyboard::Space)) pr = false;
            player.update(time);

            for (it = objects.begin(); it != objects.end();) {
                object* b = *it;
                b->update(time);
                if (b->life == 0) { it = objects.erase(it); delete b; }
                else { it++; }
            }

            for (ot = ob.begin(); ot != ob.end();) {
                object* c = *ot;
                bulletframe += 0.003 * time;
                if (bulletframe > 5) bulletframe -= 5;
                c->sprite.setTextureRect(IntRect(60 * int(bulletframe), 0, 60, 15));
                c->update(time);

                if (c->life == 0 || c->x > 1920) { ot = ob.erase(ot); delete c; }
                else { ot++; }
            }

            for (it = bonuslist.begin(); it != bonuslist.end();) {
                object* b = *it;
                if (b->Name == "bonus1") {
                    bonusframe1 += 0.002 * time;
                    if (bonusframe1 > 12) bonusframe1 -= 12;
                    b->sprite.setTextureRect(IntRect(50 * int(bonusframe1), 0, 50, 50));
                }
                else if (b->Name == "bonus2") {
                    bonusframe2 += 0.002 * time;
                    if (bonusframe2 > 12) bonusframe2 -= 12;
                    b->sprite.setTextureRect(IntRect(50 * int(bonusframe2), 250, 50, 50));
                }
                else {
                    bonusframe3 += 0.002 * time;
                    if (bonusframe3 > 12) bonusframe3 -= 12;
                    b->sprite.setTextureRect(IntRect(50 * int(bonusframe2), 600, 50, 50));
                }
                b->update(time);

                if (b->life == 0) { it = bonuslist.erase(it); delete b; }
                else { it++; }
            }
            if (Boss.life == 1) {
                bossframe += 0.005 * time;
                if (bossframe > 9) bossframe -= 9;
                Boss.sprite.setTextureRect(IntRect(530 * int(bossframe), 0, 520, 466));
                Boss.update(time);
            }
            else {
                pause = true;
            }
        }

        for (ot = ob.begin(); ot != ob.end(); ot++) {
            for (it = objects.begin(); it != objects.end(); it++) {
                object* b = *it;
                object* c = *ot;
                if (c->sprite.getGlobalBounds().intersects(b->sprite.getGlobalBounds())) {
                    c->life = 0;
                    b->life = 0;
                    player.score += 10;
                    bbh.play();
                }
                if (c->sprite.getGlobalBounds().intersects(Boss.sprite.getGlobalBounds())) {
                    c->life = 0;
                    Boss.life = 0;
                    hits.play();
                    win.sprite.setColor(Color(255, 255, 255, 255));
                }
            }
        }

        for (it = objects.begin(); it != objects.end(); it++) {
            object* b = *it;
            if (player.sprite.getGlobalBounds().intersects(b->sprite.getGlobalBounds())) {
                moveframedestroy += 0.01 * time;
                player.sprite.setTexture(te);
                player.sprite.setTextureRect(IntRect(140 * int(moveframedestroy), 0, 140, 128));
                pause = true;
                lose.sprite.setColor(Color(255, 255, 255, 255));
                if (pl == false) {
                    bbh.play();
                    pl = true;
                }
            }
        }

        if (player.sprite.getGlobalBounds().intersects(Boss.sprite.getGlobalBounds())) {
            moveframedestroy += 0.01 * time;
            player.sprite.setTexture(te);
            player.sprite.setTextureRect(IntRect(140 * int(moveframedestroy), 0, 140, 128));
            pause = true;
            lose.sprite.setColor(Color(255, 255, 255, 255));
            if (pl == false) {
                bbh.play();
                pl = true;
            }
        }

        for (it = bonuslist.begin(); it != bonuslist.end(); it++) {
            object* b = *it;
            for (ot = ob.begin(); ot != ob.end(); ot++) {
                object* c = *ot;
                if (player.sprite.getGlobalBounds().intersects(b->sprite.getGlobalBounds())) {
                    if (b->Name == "bonus1") {
                        b->life = 0;
                        player.score += 50;
                        Bonus.play();
                    }
                    if (b->Name == "bonus2") {
                        b->life = 0;
                        c->speed += 0.1;
                        Bonus.play();
                    }
                    if (b->Name == "bonus3") {
                        b->life = 0;
                        player.fullspeed += 0.01;
                        Bonus.play();
                    }
                }
            }
        }
        if (Boss.life == 1) {
            player.update(time);
        }

        ostringstream gametimeString, PlayerScore;
        gametimeString << gametime;
        PlayerScore << player.score;
        text.setString(gametimeString.str());
        textscore.setString(PlayerScore.str());

        text.setPosition(930, 0);
        textscore.setPosition(250, 0);

        Play.clear();
        Play.draw(background_play);
        Play.draw(timebar.sprite);
        Play.draw(text);
        Play.draw(textscore);
        Play.draw(plscore);
        Play.draw(undertablo.sprite);
        Play.draw(player.sprite);
        if (player.life = 1) {
            for (it = objects.begin(); it != objects.end(); it++) {
                Play.draw((*it)->sprite);
            }
        }
        for (it = ob.begin(); it != ob.end(); it++) {
            Play.draw((*it)->sprite);
        }

        for (it = bonuslist.begin(); it != bonuslist.end(); it++) {
            Play.draw((*it)->sprite);
        }
        Play.draw(Boss.sprite);
        Play.draw(pausing.sprite);
        Play.draw(win.sprite);
        Play.draw(lose.sprite);
        Play.display();
    }
    return player.score;
}

String myname() {
    RenderWindow window(VideoMode::getDesktopMode(), "name", Style::Fullscreen);

    RectangleShape background_name(Vector2f(1920, 1080));
    Texture texture_name;

    if (!texture_name.loadFromFile("image/space_menu4.png")) exit(1);
    background_name.setTexture(&texture_name);

    ImageText whatisurname("image/whatisurname.png", 370, 230, true), esc("image/esc.png", 370, 700, true), enter("image/enter.png", 1160, 700, true);

    Font font;
    font.loadFromFile("font/GTA.ttf");

    Text name;
    name.setFont(font);
    name.setCharacterSize(80);
    name.setFillColor(Color::Black);
    name.setPosition(770, 480);

    string input;
    bool isNameEntered = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.key.code == Keyboard::Enter) {
                window.close();
                return input;
            }
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }
            else if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!input.empty()) {
                        input.erase(input.size() - 1);
                        name.setString(input);
                    }
                }
                else if (event.text.unicode == '\r') {
                    isNameEntered = true;
                    break;
                }
                else if (input.size() < 15 && isalpha(event.text.unicode)) {
                    input += static_cast<char>(event.text.unicode);
                    name.setString(input);
                }
            }
        }

        window.clear();
        window.draw(background_name);
        window.draw(whatisurname.sprite);
        window.draw(esc.sprite);
        window.draw(enter.sprite);

        if (!isNameEntered) {
            window.draw(name);
        }

        window.display();
    }

    return input;
}

void writeToTextFile(string name, int score, string file) {
    ofstream filing(file + ".txt", ios::app);
    filing << name << " " << score << endl;
    filing.close();
}

void sort_file(const string& filename)
{
    ifstream input_file(filename);
    vector <playerscoring> playscore;
    string name;
    int score;
    while (input_file >> name >> score) {
        playscore.push_back({ name, score });
    }

    sort(playscore.begin(), playscore.end());
    ofstream output_file(filename);
    for (const auto& playerscoring : playscore) {
        output_file << playerscoring.name << " " << playerscoring.score << "\n";
    }
}