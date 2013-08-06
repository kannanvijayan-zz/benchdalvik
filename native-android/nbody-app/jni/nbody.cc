
#include <jni.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double DoubleTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (((double)tv.tv_usec) / 1000000);
}

double PI = M_PI;
double SOLAR_MASS = 4 * PI * PI;
double DAYS_PER_YEAR = 365.24;

struct Body
{
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double mass;

    Body(double x, double y, double z, double vx, double vy, double vz, double mass)
      : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), mass(mass)
    {}

    Body *offsetMomentum(double px, double py, double pz) {
       vx = -px / SOLAR_MASS;
       vy = -py / SOLAR_MASS;
       vz = -pz / SOLAR_MASS;
       return this;
    }
};

Body *Jupiter(){
   return new Body(
      4.84143144246472090e+00,
      -1.16032004402742839e+00,
      -1.03622044471123109e-01,
      1.66007664274403694e-03 * DAYS_PER_YEAR,
      7.69901118419740425e-03 * DAYS_PER_YEAR,
      -6.90460016972063023e-05 * DAYS_PER_YEAR,
      9.54791938424326609e-04 * SOLAR_MASS
   );
}

Body *Saturn(){
   return new Body(
      8.34336671824457987e+00,
      4.12479856412430479e+00,
      -4.03523417114321381e-01,
      -2.76742510726862411e-03 * DAYS_PER_YEAR,
      4.99852801234917238e-03 * DAYS_PER_YEAR,
      2.30417297573763929e-05 * DAYS_PER_YEAR,
      2.85885980666130812e-04 * SOLAR_MASS
   );
}

Body *Uranus(){
   return new Body(
      1.28943695621391310e+01,
      -1.51111514016986312e+01,
      -2.23307578892655734e-01,
      2.96460137564761618e-03 * DAYS_PER_YEAR,
      2.37847173959480950e-03 * DAYS_PER_YEAR,
      -2.96589568540237556e-05 * DAYS_PER_YEAR,
      4.36624404335156298e-05 * SOLAR_MASS
   );
}

Body *Neptune(){
   return new Body(
      1.53796971148509165e+01,
      -2.59193146099879641e+01,
      1.79258772950371181e-01,
      2.68067772490389322e-03 * DAYS_PER_YEAR,
      1.62824170038242295e-03 * DAYS_PER_YEAR,
      -9.51592254519715870e-05 * DAYS_PER_YEAR,
      5.15138902046611451e-05 * SOLAR_MASS
   );
}

Body *Sun(){
   return new Body(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SOLAR_MASS);
}


struct NBodySystem {
    Body **bodies;
    int nbodies;

    NBodySystem(Body **bodies, int nbodies)
      : bodies(bodies), nbodies(nbodies)
    {
       double px = 0.0;
       double py = 0.0;
       double pz = 0.0;
       int size = nbodies;
       for (int i=0; i<size; i++){
          Body *b = bodies[i];
          double m = b->mass;
          px += b->vx * m;
          py += b->vy * m;
          pz += b->vz * m;
       }
       bodies[0]->offsetMomentum(px,py,pz);
    }

    ~NBodySystem() {
        for (int i = 0; i < nbodies; i++) {
            delete bodies[i];
        }
        delete bodies;
    }

    void advance(double dt) {
       double dx, dy, dz, distance, mag;
       int size = nbodies;

       for (int i=0; i<size; i++) {
          Body *bodyi = bodies[i];
          for (int j=i+1; j<size; j++) {
             Body *bodyj = bodies[j];
             dx = bodyi->x - bodyj->x;
             dy = bodyi->y - bodyj->y;
             dz = bodyi->z - bodyj->z;

             distance = sqrt(dx*dx + dy*dy + dz*dz);
             mag = dt / (distance * distance * distance);

             bodyi->vx -= dx * bodyj->mass * mag;
             bodyi->vy -= dy * bodyj->mass * mag;
             bodyi->vz -= dz * bodyj->mass * mag;

             bodyj->vx += dx * bodyi->mass * mag;
             bodyj->vy += dy * bodyi->mass * mag;
             bodyj->vz += dz * bodyi->mass * mag;
          }
       }

       for (int i=0; i<size; i++) {
          Body *body = this->bodies[i];
          body->x += dt * body->vx;
          body->y += dt * body->vy;
          body->z += dt * body->vz;
       }
    }

    double energy() {
       double dx, dy, dz, distance;
       double e = 0.0;
       int size = nbodies;

       for (int i=0; i<size; i++) {
          Body *bodyi = this->bodies[i];

          e += 0.5 * bodyi->mass *
             ( bodyi->vx * bodyi->vx
             + bodyi->vy * bodyi->vy
             + bodyi->vz * bodyi->vz );

          for (int j=i+1; j<size; j++) {
             Body * bodyj = this->bodies[j];
             dx = bodyi->x - bodyj->x;
             dy = bodyi->y - bodyj->y;
             dz = bodyi->z - bodyj->z;

             distance = sqrt(dx*dx + dy*dy + dz*dz);
             e -= (bodyi->mass * bodyj->mass) / distance;
          }
       }
       return e;
    }
};


volatile double ret = 0.0;

void runBodies() {
    for ( int n = 3; n <= 24; n *= 2 ) {
        Body **bodyArray = new Body *[5];
        bodyArray[0] = Sun();
        bodyArray[1] = Jupiter();
        bodyArray[2] = Saturn();
        bodyArray[3] = Uranus();
        bodyArray[4] = Neptune();
        NBodySystem *bodies = new NBodySystem(bodyArray, 5);

        int max = n * 100;
            
        ret += bodies->energy();
        for (int i=0; i<max; i++){
            bodies->advance(0.01);
        }
        ret += bodies->energy();

        delete bodies;
    }
}

extern "C" {
jdouble
Java_ca_vijayan_dalvikbench_native_1nbody_NBodyApp_runBench( JNIEnv* env,
                                                  jobject thiz )
{
    double d1 = DoubleTime();
    for (int i = 0; i < 1000; i++) {
        runBodies();
    }
    double d2 = DoubleTime();
    return (jdouble)(d2-d1);
}
}
