void init(int length[3]) {
    length[0] = 0;
    length[1] = 0;
    length[2] = 0;

    return;
}
void add(int length[3], int i) {
    length[2] += i;
    length[1] += length[2] / 12;
    length[2] %= 12;

    length[0] += length[1] / 3;
    length[1] %= 3;

    return;
}
void sum(int lengtha[3], int lengthb[3], int lengthc[3]) {
    init(lengthc);
    int sum1 = 36 * lengtha[0] + 12 * lengtha[1] + lengtha[2];
    int sum2 = 36 * lengthb[0] + 12 * lengthb[1] + lengthb[2];

    add(lengthc, sum1 + sum2);

    return;
}
void diff(int lengtha[3], int lengthb[3], int lengthc[3]) {
    init(lengthc);
    int sum1 = 36 * lengtha[0] + 12 * lengtha[1] + lengtha[2];
    int sum2 = 36 * lengthb[0] + 12 * lengthb[1] + lengthb[2];

    add(lengthc, sum1 - sum2);

}