#include "MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define WIDTH 800
#define WIDTH 1280
// #define HEIGHT 600
#define HEIGHT 1080
// #define MAP_WIDTH 8
#define MAP_WIDTH 24
// #define MAP_HEIGHT 8
#define MAP_HEIGHT 24
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

// Структура для игрока
typedef struct s_player {
    double x;      // позиция x
    double y;      // позиция y  
    double angle;  // угол поворота
    double dx;     // направление x (cos угла)
    double dy;     // направление y (sin угла)
} t_player;

// Структура для игры
typedef struct s_game {
    mlx_t *mlx;
    mlx_image_t *image;
    t_player player;
    int map[MAP_HEIGHT][MAP_WIDTH];
} t_game;

// Простая карта (1 = стена, 0 = пустота)
/* int world_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1}
}; */

// int worldMap[mapWidth][mapHeight]=
int world_map[MAP_HEIGHT][MAP_WIDTH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


/******************************************************************************/

// Функция для установки пикселя в изображение (MLX42 использует RGBA)
void put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height) {
        mlx_put_pixel(image, x, y, color);
    }
}

// Создание цвета в формате RGBA
uint32_t create_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// Основная функция raycasting
void raycast(t_game *game)
{
    int x;
    
    // Проходим по каждому столбцу экрана
	printf("player.x %f, player.y %f, player.dx %f, player.dy %f, plaer angle %f, \n",\
			game->player.x, game->player.y, game->player.dx, game->player.dy, game->player.angle);
    for (x = 0; x < WIDTH; x++) {
        // Вычисляем угол луча для данного столбца
        double camera_x = 2 * x / (double)WIDTH - 1; // от -1 до 1
        double ray_angle = game->player.angle + atan(camera_x * 0.9); // поле зрения (FOV)
        
        // Направление луча
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);
        
        // Текущая позиция луча
        double ray_x = game->player.x;
        double ray_y = game->player.y;
        
        // Шаг луча (чем меньше, тем точнее, но медленнее)
        double step = 0.002;
        double distance = 0;
		// printf("camera_x - %f, ray_angel, %f, ray_dx %f, ray_dy %f, ray_x %f, ray_y %f\n", camera_x, ray_angle, ray_dx, ray_dy, ray_x, ray_y);
		printf("%f, %f\n", ray_dx, ray_y);
        
        // Кастуем луч пока не попадем в стену
        while (distance < 20) { // максимальная дальность
            ray_x += ray_dx * step;
            ray_y += ray_dy * step;
            distance += step;
            
            // Проверяем координаты карты
            int map_x = (int)ray_x;
            int map_y = (int)ray_y;
            
            // Если вышли за границы карты или попали в стену
            if (map_x < 0 || map_x >= MAP_WIDTH || 
                map_y < 0 || map_y >= MAP_HEIGHT || 
                world_map[map_y][map_x] == 1) {
                break;
            }
        }
        
        // Исправляем fish-eye эффект
        distance *= cos(ray_angle - game->player.angle);
        
        // Высота стены на экране (обратно пропорциональна расстоянию)
        int wall_height = (int)(HEIGHT / distance);
        if (wall_height > HEIGHT) wall_height = HEIGHT;
        
        // Рисуем вертикальную линию стены
        int wall_start = (HEIGHT - wall_height) / 2;
        int wall_end = wall_start + wall_height;
        
        int y;
        for (y = 0; y < HEIGHT; y++) {
            if (y < wall_start) {
                // Потолок (небо)
                put_pixel(game->image, x, y, create_color(135, 206, 235, 255)); // светло-голубой
            } else if (y >= wall_start && y < wall_end) {
                // Стена (цвет зависит от расстояния для эффекта затемнения)
                int brightness = (int)(255 / (1 + distance * 0.1));
                if (brightness > 255) brightness = 255;
                if (brightness < 50) brightness = 50;
                put_pixel(game->image, x, y, create_color(brightness, brightness, brightness, 255));
            } else {
                // Пол
                put_pixel(game->image, x, y, create_color(34, 139, 34, 255)); // зеленый
            }
        }
    }
}

// Обработка движения игрока
void handle_movement(t_game *game)
{
    double new_x, new_y;
    
    // W - движение вперед
    if (mlx_is_key_down(game->mlx, MLX_KEY_W)) {
        new_x = game->player.x + game->player.dx * MOVE_SPEED;
        new_y = game->player.y + game->player.dy * MOVE_SPEED;
        
        // Проверяем коллизии
        if (world_map[(int)new_y][(int)new_x] == 0) {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    // S - движение назад
    if (mlx_is_key_down(game->mlx, MLX_KEY_S)) {
        new_x = game->player.x - game->player.dx * MOVE_SPEED;
        new_y = game->player.y - game->player.dy * MOVE_SPEED;
        
        if (world_map[(int)new_y][(int)new_x] == 0) {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    // A - поворот влево
    if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
        game->player.angle -= ROT_SPEED;
        game->player.dx = cos(game->player.angle);
        game->player.dy = sin(game->player.angle);
    }
    
    // D - поворот вправо
    if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
        game->player.angle += ROT_SPEED;
        game->player.dx = cos(game->player.angle);
        game->player.dy = sin(game->player.angle);
    }
    
    // ESC - выход
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) {
        mlx_close_window(game->mlx);
    }
}

// Главный игровой цикл
void game_loop(void *param)
{
    t_game *game = (t_game *)param;
    
    // Обрабатываем движение
    handle_movement(game);
    
    // Выполняем raycasting
    raycast(game);
}

int main()
{
    t_game game;
    
    // Инициализация MLX42
    game.mlx = mlx_init(WIDTH, HEIGHT, "Simple Raycaster - MLX42", false);
    if (!game.mlx) {
        printf("Ошибка инициализации MLX42\n");
        return (EXIT_FAILURE);
    }
    
    // Создание изображения для рендеринга
    game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    if (!game.image) {
        printf("Ошибка создания изображения\n");
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }
    
    // Добавляем изображение в окно
    if (mlx_image_to_window(game.mlx, game.image, 0, 0) < 0) {
        printf("Ошибка добавления изображения в окно\n");
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }
    
    // Инициализация игрока
    game.player.x = 4.0;      // стартовая позиция x
    game.player.y = 4.0;      // стартовая позиция y
    game.player.angle = 0.0;  // стартовый угол (смотрим вправо)
    game.player.dx = cos(game.player.angle);
    game.player.dy = sin(game.player.angle);
    
    // Копируем карту
    int i, j;
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            game.map[i][j] = world_map[i][j];
        }
    }
    
    // Устанавливаем callback для главного цикла
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    // Запуск главного цикла
    mlx_loop(game.mlx);
    
    // Очистка ресурсов
    mlx_terminate(game.mlx);
    
    return (EXIT_SUCCESS);
}
