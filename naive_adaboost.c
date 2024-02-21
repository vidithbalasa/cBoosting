#include <stdio.h>
#include <math.h>

void buildTree(
    double X[][2], double* y, int N, int M, double* w,
    int *best_feat, double *best_split, double *error,
    float* preds
) {
    double best_error = 99999.0;

    for (int f=0; f<M; f++ ) { // Iterate through features first
        for (int s=0; s<2; s++) {
            double split = s - 0.5;
            int y_hat[N];
            double weighted_error = 0.0;
            double weight_sum = 0.0;

            for (int i=0; i<N; i++) {
                if (X[i][f] < split)  y_hat[i] = -1;
                else y_hat[i] = 1;

                if (y[i] != y_hat[i]) weighted_error += w[i];
                weight_sum += w[i];
            }

            double err = weighted_error / weight_sum;
            if (err < best_error) {
                *best_feat = f;
                *best_split = split;
                *error = err;
                best_error = err;
            }
        }
    }
    return;
}

void adaBoost(double X[][2], double* y, int N, int M, int iters, double preds[][4], double *tree_weights) {
    // Initialize Weights
    double w[N];
    for (int i=0; i<N; i++) w[i] = 1.0/N;

    // Build Trees 
    for (int i=0; i<1; i++) {
        int best_feat; double best_split, error;
        buildTree(X, y, N, M, w, &best_feat, &best_split, &error);

        double error_proportion = (1-error) / error;
        double alpha = log(error_proportion);

        preds
    }


    return;
}

int main(void) {
    int N = 4; 
    int M = 2;
    double X[][2] = {{0,-1}, {1,0}, {-1,0}, {0,1}};
    double y[] = {-1, 1, 1, -1};
    int iter = 10;
    double preds[iter][4];
    double tree_weights[iter];

    adaBoost(X, y, N, M, iter, preds, tree_weights);
    
    return 0;
}
