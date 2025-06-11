#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define PADDLE_W 10
#define PADDLE_H 80
#define BALL_SIZE 10
#define FPS 60

int main(void) {
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    bool redraw = true;

    float paddle_y = SCREEN_H/2 - PADDLE_H/2;
    float cpu_paddle_y = SCREEN_H/2 - PADDLE_H/2;
    float ball_x = SCREEN_W/2;
    float ball_y = SCREEN_H/2;
    float ball_dx = -4.0;
    float ball_dy = 4.0;

    al_start_timer(timer);

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(al_key_down(&ev.keyboard, ALLEGRO_KEY_UP)) {
                paddle_y -= 5.0;
            }
            if(al_key_down(&ev.keyboard, ALLEGRO_KEY_DOWN)) {
                paddle_y += 5.0;
            }

            ball_x += ball_dx;
            ball_y += ball_dy;

            if(ball_y < 0 || ball_y > SCREEN_H - BALL_SIZE) {
                ball_dy = -ball_dy;
            }
            if(ball_x < PADDLE_W && ball_y > paddle_y && ball_y < paddle_y + PADDLE_H) {
                ball_dx = -ball_dx;
            }
            if(ball_x > SCREEN_W - PADDLE_W - BALL_SIZE) {
                if(ball_y > cpu_paddle_y && ball_y < cpu_paddle_y + PADDLE_H) {
                    ball_dx = -ball_dx;
                } else {
                    ball_x = SCREEN_W/2;
                    ball_y = SCREEN_H/2;
                }
            }

            // simple AI
            if(cpu_paddle_y + PADDLE_H/2 < ball_y)
                cpu_paddle_y += 3.0;
            else
                cpu_paddle_y -= 3.0;

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if(redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            al_draw_filled_rectangle(0, paddle_y, PADDLE_W, paddle_y+PADDLE_H,
                                    al_map_rgb(255,255,255));
            al_draw_filled_rectangle(SCREEN_W-PADDLE_W, cpu_paddle_y,
                                    SCREEN_W, cpu_paddle_y+PADDLE_H,
                                    al_map_rgb(255,255,255));
            al_draw_filled_circle(ball_x, ball_y, BALL_SIZE, al_map_rgb(255,255,255));

            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}
