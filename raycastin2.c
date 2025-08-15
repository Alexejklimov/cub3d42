#include "MLX42.h"
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define WIDTH 800
#define WIDTH 2800
// #define HEIGHT 600
#define HEIGHT 1720
// #define MAP_WIDTH 8
#define MAP_WIDTH 24
// #define MAP_HEIGHT 8
#define MAP_HEIGHT 24
#define MOVE_SPEED 0.05
// #define ROT_SPEED 0.05

// Структура для игрока
typedef struct s_player {
    double x;      // позиция x
    double y;      // позиция y  
    double angle;  // угол поворота
    double planeX;  // угол поворота
    double planeY;  // угол поворота
    double dx;     // направление x (cos угла)
    double dy;     // направление y (sin угла)
} t_player;

// Структура для игры
typedef struct s_game {
    mlx_t 		*mlx;
    mlx_image_t *image;
    t_player 	player;
	double		move_speed;
	double		move_rotate;
	double		time;
	double		oldtime;
	double		first_frame;
    int map[MAP_HEIGHT][MAP_WIDTH];
} t_game;



double	ft_get_time();

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
    int x = 0;
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
    double cameraX;
    double rayDirX, rayDirY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist; 
    int stepX, stepY;
    int side;
    // int hit = 0;
    
    // Инициализация позиции и направления игрока
    posX = game->player.x;
    posY = game->player.y;
    dirX = game->player.dx;
    dirY = game->player.dy;
    planeX = game->player.planeX;
    planeY = game->player.planeY;
    
    // Отладочный вывод (можно убрать в финальной версии)
    /* printf("player.x %f, player.y %f, player.dx %f, player.dy %f, player angle %f\n",
           game->player.x, game->player.y, game->player.dx, game->player.dy, game->player.angle); */
    
    // Проходим по каждому столбцу экрана
    while (x < WIDTH)
    {
        // Вычисляем направление луча для текущего столбца
        cameraX = 2 * x / (double)WIDTH - 1; // координата камеры от -1 до 1
        rayDirX = dirX + planeX * cameraX;
        rayDirY = dirY + planeY * cameraX;
        
        // Текущая позиция на карте
        int mapX = (int)posX;
        int mapY = (int)posY;
        
        // Вычисляем дельта расстояния (расстояние между пересечениями сетки)
        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1 / rayDirX);
            
        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1 / rayDirY);
        
        // Определяем направление шага и начальное расстояние до стороны
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        
        // Выполняем DDA (Digital Differential Analyzer)
        // hit = 0; // Сброс флага попадания для каждого нового луча
        // while (hit == 0)
        while (1)
        {
            // Переходим к следующему пересечению сетки
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // попадание по вертикальной стороне
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // попадание по горизонтальной стороне
            }
            
            // Проверяем, попали ли мы в стену
            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT && // Добавлена проверка границ
                world_map[mapX][mapY] > 0)
				break;
                // hit = 1;
        }
        
        // Вычисляем перпендикулярное расстояние до стены (избегаем fish-eye эффекта)
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        
        // Вычисляем высоту стены на экране
        int wall_height = (int)(HEIGHT / perpWallDist);
        
        // Определяем начало и конец стены на экране
        int wall_start = (HEIGHT - wall_height) / 2;
        if (wall_start < 0)
            wall_start = 0;
            
        int wall_end = wall_start + wall_height;
        if (wall_end >= HEIGHT)
            wall_end = HEIGHT - 1;
        
        // Рисуем вертикальную линию
        for (int y = 0; y < HEIGHT; y++)
        {
            if (y < wall_start)
            {
                // --- Потолок с затемнением ---
                double ceiling_distance = HEIGHT / (2.0 * y - HEIGHT); // Estimate distance
                if (ceiling_distance < 0.1) ceiling_distance = 0.1;

                int brightness = (int)(255 / (1 + ceiling_distance * 0.1));
                if (brightness > 255) brightness = 255;
                if (brightness < 50) brightness = 50;

                // Светло-голубой, затемнённый
                put_pixel(game->image, x, y, create_color(
                    brightness * 135 / 255,
                    brightness * 206 / 255,
                    brightness * 235 / 255,
                    255
                ));
            }
            else if (y >= wall_start && y <= wall_end) // Исправлено: y <= wall_end
            {
                // Стена с эффектом затемнения по расстоянию
                int brightness = (int)(255 / (1 + perpWallDist * 0.1));
                if (brightness > 255) brightness = 255;
                if (brightness < 50) brightness = 50;
                
                // Можно добавить различные цвета для разных сторон стены
                if (side == 1) // горизонтальные стены чуть темнее
                    brightness = brightness * 0.8;
                
                put_pixel(game->image, x, y, create_color(brightness, brightness, brightness, 255));
            }
            else
            {
                // Пол
                put_pixel(game->image, x, y, create_color(34, 139, 34, 255)); // зеленый
            }
        }
        x++;
    }
	
}

// Обработка движения игрока


void handle_movement(t_game *game)
{
    double new_x, new_y;
    double dirX = game->player.dx;
    double dirY = game->player.dy;
    double planeX = game->player.planeX;
    double planeY = game->player.planeY;

	double	ROT_SPEED = game->move_rotate;
    
    // W - движение вперед
    if (mlx_is_key_down(game->mlx, MLX_KEY_W)) {
        // new_x = game->player.x + game->player.dx * MOVE_SPEED;
        // new_y = game->player.y + game->player.dy * MOVE_SPEED;
        new_x = game->player.x + game->player.dx * game->move_speed;
        new_y = game->player.y + game->player.dy * game->move_speed;
        
        // Проверяем границы карты и коллизии
        if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT) {
            // Проверяем X координату отдельно
            if (world_map[(int)new_x][(int)game->player.y] == 0) {
                game->player.x = new_x;
            }
            // Проверяем Y координату отдельно
            if (world_map[(int)game->player.x][(int)new_y] == 0) {
                game->player.y = new_y;
            }
        }
        printf("Position: %f, %f\n", game->player.x, game->player.y);
    }
    
    // S - движение назад
    if (mlx_is_key_down(game->mlx, MLX_KEY_S)) {
        // new_x = game->player.x - game->player.dx * MOVE_SPEED;
        // new_y = game->player.y - game->player.dy * MOVE_SPEED;
        new_x = game->player.x - game->player.dx * game->move_speed;
        new_y = game->player.y - game->player.dy * game->move_speed;
        
        // Проверяем границы карты и коллизии
        if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT) {
            // Проверяем X координату отдельно
            if (world_map[(int)new_x][(int)game->player.y] == 0) {
                game->player.x = new_x;
            }
            // Проверяем Y координату отдельно
            if (world_map[(int)game->player.x][(int)new_y] == 0) {
                game->player.y = new_y;
            }
        }
        printf("Position: %f, %f\n", game->player.x, game->player.y);
    }
    
    // A - поворот влево
    if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
        game->player.angle += ROT_SPEED;
        
        // Поворачиваем вектор направления
        double oldDirX = dirX;
        game->player.dx = dirX * cos(ROT_SPEED) - dirY * sin(ROT_SPEED);
        game->player.dy = oldDirX * sin(ROT_SPEED) + dirY * cos(ROT_SPEED);
        
        // Поворачиваем плоскость камеры
        double oldPlaneX = planeX;
        game->player.planeX = planeX * cos(ROT_SPEED) - planeY * sin(ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(ROT_SPEED) + planeY * cos(ROT_SPEED);
    }
    
    // D - поворот вправо
    if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
        game->player.angle += ROT_SPEED;
        
        // Поворачиваем вектор направления
        double oldDirX = dirX;
        game->player.dx = dirX * cos(-ROT_SPEED) - dirY * sin(-ROT_SPEED);
        game->player.dy = oldDirX * sin(-ROT_SPEED) + dirY * cos(-ROT_SPEED);
        
        // Поворачиваем плоскость камеры
        double oldPlaneX = planeX;
        game->player.planeX = planeX * cos(-ROT_SPEED) - planeY * sin(-ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(-ROT_SPEED) + planeY * cos(-ROT_SPEED);
    }
    
    // ESC - выход
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) {
        mlx_close_window(game->mlx);
    }
}

/* void handle_movement(t_game *game)
{
    double new_x, new_y;
	double	dirX = game->player.dx;
	double	dirY = game->player.dy;
	double	planeX = game->player.planeX;
	double	planeY = game->player.planeY;
    
    // W - движение вперед
    if (mlx_is_key_down(game->mlx, MLX_KEY_W)) {
        new_x = game->player.x + game->player.dx * MOVE_SPEED;
		if (world_map[(int)new_x][(int)game->player.y] == 0)
			game->player.x += game->player.dx * MOVE_SPEED;
        new_y = game->player.y + game->player.dy * MOVE_SPEED;
		if (world_map[(int)game->player.x][(int)new_y] == 0)
			game->player.y += game->player.dy * MOVE_SPEED;
        
        // Проверяем коллизии
       //  if (world_map[(int)new_y][(int)new_x] == 0) {
       //     game->player.x = new_x;
       //     game->player.y = new_y;
       // } 
		printf("%f, %f\n", new_x, new_y);
    }
    
    // S - движение назад
    if (mlx_is_key_down(game->mlx, MLX_KEY_S)) {
        new_x = game->player.x - game->player.dx * MOVE_SPEED;
		if (world_map[(int)new_x][(int)game->player.y] == 0)
			game->player.x -= game->player.dx * MOVE_SPEED;

        new_y = game->player.y - game->player.dy * MOVE_SPEED;
		if (world_map[(int)game->player.x][(int)new_y] == 0)
			game->player.y -= game->player.dy * MOVE_SPEED;
        
        // if (world_map[(int)new_y][(int)new_x] == 0) {
        //    game->player.x = new_x;
        //    game->player.y = new_y; 
        //}
		printf("%f, %f\n", new_x, new_y);
    }
    
    // A - поворот влево
    if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
        game->player.angle -= ROT_SPEED;
        // game->player.dx = cos(game->player.angle);
        // game->player.dy = sin(game->player.angle);
		double	oldDirx = dirX;
        game->player.dx = cos(game->player.angle);
		game->player.dx = dirX * cos(ROT_SPEED) - dirY * sin(ROT_SPEED);
        game->player.dy = sin(game->player.angle);
        game->player.dy = oldDirx * sin(ROT_SPEED) + dirY * cos(ROT_SPEED);
		double	oldplaneX = planeX;
		game->player.planeX = planeX * cos(ROT_SPEED) - planeY * sin(ROT_SPEED);
		game->player.planeY = oldplaneX * sin(ROT_SPEED) + planeY * cos(ROT_SPEED);

    }
    
    // D - поворот вправо
    if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
        game->player.angle += ROT_SPEED;
		double	oldDirx = dirX;
        game->player.dx = cos(game->player.angle);
		game->player.dx = dirX * cos(-ROT_SPEED) - dirY * sin(-ROT_SPEED);
        game->player.dy = sin(game->player.angle);
        game->player.dy = oldDirx * sin(-ROT_SPEED) + dirY * cos(-ROT_SPEED);
		double	oldplaneX = planeX;
		game->player.planeX = planeX * cos(-ROT_SPEED) - planeY * sin(-ROT_SPEED);
		game->player.planeY = oldplaneX * sin(-ROT_SPEED) + planeY * cos(-ROT_SPEED);
    }
    
    // ESC - выход
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) {
        mlx_close_window(game->mlx);
    }
} */


// Главный игровой цикл
void game_loop(void *param)
{
    t_game *game = (t_game *)param;
	// timing for input and FPS counter
	// 
	double	time;
	double	frame_time;
	

	time = ft_get_time();
	if (game->first_frame)
	{
		game->oldtime = time;
		frame_time = 0.016;
		game->first_frame = 0;
		
	}
	else
	{
		frame_time = (time - game->oldtime) / 1000.0;
	}
	
	printf("Time: %f ms, FrameTime: %f s\n", time, frame_time);
    if (frame_time > 0)
        printf("FPS: %.2f\n", 1.0 / frame_time);
    
    game->oldtime = time;
	game->move_speed = frame_time * 5.0;
	game->move_rotate = frame_time * 3.0;
	printf("move speed: %f, rotate speed: %f\n", game->move_speed, game->move_rotate);
	
	// printf("Milliseconds since %f, %f\n", time, frameTime);
	// printf("FrameTime %f\n", 1.0 / frameTime);

		

    
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
    // game.player.x = 22.0;      // стартовая позиция x
    game.player.y = 4.0;      // стартовая позиция y
    // game.player.y = 12.0;      // стартовая позиция y
    game.player.angle = 0.0;  // стартовый угол (смотрим вправо)
    // game.player.dx = cos(game.player.angle);
    game.player.dx = -1;
    // game.player.dy = sin(game.player.angle);
    game.player.dy = 0;
	game.player.planeX = 0;
	game.player.planeY = 0.66;
	game.time = 0;
	game.oldtime = 0;
    
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


double	ft_get_time()
{
	double	time = 0;
	struct timeval tv;
	
	
	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("error gettimeofday");
		exit (EXIT_FAILURE);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}