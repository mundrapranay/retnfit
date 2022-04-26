#include <assert.h>
#include <stdlib.h>
#include "gn.h"

#define TRUE 1
#define FALSE 0

int **get_parent()
{
    int **parent;
    int *parent_data;
    parent_data = (int*)malloc(3*2*sizeof(int));
    parent = (int**)malloc(3*sizeof(int*));
    for (int i=0;i<3;i++) {
        parent[i] = &(parent_data[i*2]);
    }
    parent[0][0] = 1;
    parent[0][1] = 2;
    parent[1][0] = 0;
    parent[1][1] = 2;
    parent[2][0] = 0;
    parent[2][1] = 1;
    return parent;
}

int **get_outcome()
{

    int **outcome;
    int *outcome_data;
    outcome_data = (int*)malloc(3*9*sizeof(int));
    outcome = (int**)malloc(3*sizeof(int*));
    for (int i=0;i<3;i++) {
        outcome[i] = &(outcome_data[i*9]);
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<9;j++) {
            outcome[i][j] = 0;
        }
    }
    outcome[0][3] = -1;
    outcome[2][3] = 1;
    return outcome;
}

void test_score(const int *i_exp,
                const int *i_node,
                const int *outcome,
                const double *value,
                const int *is_perturbation,
                int len_i_exp)
{
    struct network net;
    struct experiment_set e_set;
    int max_states = 10;
    int max_parents = 2;

    double limit = 7.464032;
    // Initialize data
    experiment_set_init(&e_set, len_i_exp, i_exp, i_node, outcome, value, is_perturbation);
    printf("Intialized experiment\n");
    network_init(&net, e_set.n_node, max_parents);
    printf("Intialized network\n");
    net.parent = get_parent();
    net.outcome = get_outcome();
    printf("Set parents and outcomes\n");

    // CPU score
    trajectory_t trajectories = trajectories_new(e_set.n_experiment, max_states, e_set.n_node);
    printf("Initialized trajectories\n");
    double cpu_score = score(&net, &e_set, trajectories, limit, max_states);
    printf("CPU score: %lf\n", cpu_score);

    // load data into GPU
    // network_t d_net = load_network_to_gpu(&net);
    // experiment_set_t d_e_set = load_experiment_set_to_gpu(&e_set);
    // trajectory_t d_trajectories = new_trajectory_gpu(d_e_set->n_experiment, max_states, d_e_set->n_node, trajectories);
    // double gpu_score = cuda_score_host(d_net, d_e_set, d_trajectories, limit, max_states);
    // printf("Score:%lf\n",gpu_score);
}

int main()
{
    const int i_exp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         2, 2, 2, 2, 2, 2, 2, 2, 2,
                         3, 3, 3, 3, 3, 3, 3, 3, 3,
                         4, 4, 4, 4, 4, 4, 4, 4, 4,
                         5, 5, 5, 5, 5, 5, 5, 5, 5,
                         6, 6, 6, 6, 6, 6, 6, 6, 6,
                         7, 7, 7, 7, 7, 7, 7, 7, 7,
                         8, 8, 8, 8, 8, 8, 8, 8, 8,
                         9, 9, 9, 9, 9, 9, 9, 9, 9,
                         10, 10, 10, 10, 10, 10, 10, 10, 10,
                         11, 11, 11, 11, 11, 11, 11, 11, 11,
                         12, 12, 12, 12, 12, 12, 12, 12, 12,
                         13, 13, 13, 13, 13, 13, 13, 13, 13,
                         14, 14, 14, 14, 14, 14, 14, 14, 14,
                         15, 15, 15, 15, 15, 15, 15, 15, 15,
                         16, 16, 16, 16, 16, 16, 16, 16, 16,
                         17, 17, 17, 17, 17, 17, 17, 17, 17};

    const int i_node[] = {0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2,
                          0, 0, 0, 1, 1, 1, 2, 2, 2};

    const int outcome[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1,
                           -1, 0, 1, -1, 0, 1, -1, 0, 1};

    const double value[] = {2, 1, 0, 1, 0, 1, 2, 1, 0,
                            1, 0, 1, 2, 1, 0, 0, 1, 2,
                            1, 0, 1, 1, 0, 1, 2, 1, 0,
                            0, 1, 2, 1, 0, 1, 0, 1, 2,
                            1, 0, 1, 0, 1, 2, 2, 1, 0,
                            1, 0, 1, 1, 0, 1, 0, 1, 2,
                            2, 1, 0, 1, 0, 1, 2, 1, 0,
                            0, 1, 2, 1, 0, 1, 0, 1, 2,
                            1, 0, 1, 2, 1, 0, 0, 1, 2,
                            1, 0, 1, 0, 1, 2, 2, 1, 0,
                            2, 1, 0, 2, 1, 0, 1, 0, 1,
                            0, 1, 2, 0, 1, 2, 1, 0, 1,
                            2, 1, 0, 0, 1, 2, 2, 1, 0,
                            0, 1, 2, 2, 1, 0, 0, 1, 2,
                            2, 1, 0, 1, 0, 1, 0, 1, 2,
                            0, 1, 2, 1, 0, 1, 2, 1, 0,
                            1, 0, 1, 2, 1, 0, 2, 1, 0,
                            1, 0, 1, 0, 1, 2, 0, 1, 2};

    const int is_perturbation[] = {TRUE, TRUE, TRUE,
                                   FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,
                                   TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE,
                                   TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,
                                   FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};

    int len_i_exp = sizeof(i_exp) / sizeof(i_exp[0]); 

    test_score(i_exp, i_node, outcome, value, is_perturbation, len_i_exp);
    return 0;
}
