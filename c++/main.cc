#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "time.h"

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 color(const ray& r, hitable *world) {
  hit_record rec;
  if (world -> hit(r, 0.001, FLT_MAX, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * color( ray(rec.p, target - rec.p), world);
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 800;
  int ny = 400;
  int ns = 100;

  // ppm header
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // list of objects
  hitable *list[5];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(1, 0, -2), 0.5);
  list[2] = new sphere(vec3(2, 0, -3), 0.5);
  list[3] = new sphere(vec3(3, 0, -4), 0.5);
  list[4] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 5);
  camera cam;

  // timing
  clock_t begin = clock();

  // main loop
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        vec3 p = r.point_at_parameter(2.0);
        col += color(r, world);
      }

      col /= float(ns);
      col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      //printf("col:%d, row:%d r:%d g:%d b:%d\n", i, j, ir, ig, ib);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  fprintf(stderr, "Rendered in [%f] seconds\n", time_spent);
}
