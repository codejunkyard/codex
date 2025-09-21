import pygame, sys

pygame.init()
WIDTH, HEIGHT = 400, 300
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pygame Example")
clock = pygame.time.Clock()

x, y = 50, 50
dx, dy = 3, 2
radius = 20

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    x += dx
    y += dy

    if x - radius <= 0 or x + radius >= WIDTH:
        dx = -dx
    if y - radius <= 0 or y + radius >= HEIGHT:
        dy = -dy

    screen.fill((30, 30, 30))
    pygame.draw.circle(screen, (255, 100, 100), (x, y), radius)
    pygame.display.flip()
    clock.tick(60)
