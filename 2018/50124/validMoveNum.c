int validMoveNum(int r, int c, int n, int visited[100][100]){
    if(r < 0 || r >= n || c < 0 || c >= n ||
        visited[r][c] != 0)
            return -1;
    int dir[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1},
                        {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

    int count = 0;
    for(int i = 0; i < 8; i++){
        int r_next = r + dir[i][0];
        int c_next = c + dir[i][1];

        if(r_next < 0 || r_next >= n || c_next < 0 || c_next >= n || visited[r_next][c_next] != 0)
            continue;
        
        count++;
    }

    return count;
}

