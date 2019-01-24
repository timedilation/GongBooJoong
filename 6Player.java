package dwg.othello.player;

import java.util.Random;

import dwg.othello.GameUtil;
import dwg.othello.Position;

public class 6Player implements Player {
    // searchLevel should be odd number (opposite's turn).
    final static int searchLevel = 3;

    class PositionWithOppositeStones {
        Position position;
        int oppositeStones;

        PositionWithOppositeStones(Position pos, int stones) {
            position = pos;
            oppositeStones = stones;
        }
    }

    void copyBoard(int[][] to, int[][] from) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                to[i][j] = from[i][j];
            }
        }
    }

    // Minimize opponent's stones in next searchLevel.
    PositionWithOppositeStones FindNextPosition(int[][] board, int myColor, int turn, int level) {
        Random r = new Random();
        // searchLevel should be always odd number (opposite turn).
        if (level == searchLevel) {
            // Assume that opponent player will choose maximize stones position.
            int myStones = 1;  // New stone!
            int maxGainStones = 0;
            Position[] candidates = new Position[64];
            int numCandidates = 0;
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board[i][j] == turn) {
                        ++myStones;
                    }
                    Position p = new Position(i, j);
                    int gainStones = GameUtil.TestPutStone(board, turn, p);
                    if (maxGainStones == gainStones) {
                        candidates[numCandidates++] = p;
                    } else if (maxGainStones < gainStones) {
                        numCandidates = 0;
                        maxGainStones = gainStones;
                        candidates[numCandidates++] = p;
                    }
                }
            }

            return new PositionWithOppositeStones(candidates[r.nextInt(numCandidates)], myStones + maxGainStones);
        }

        int[][] tempBoard = new int[8][8];
        PositionWithOppositeStones candidates[] = new PositionWithOppositeStones[64];
        int numCandidates = 0;
        // If my turn, minimize opponent player stone. Otherwise, maximize opponent player stone.
        int candidateStones = (myColor == turn) ? 100 : 0;
        copyBoard(tempBoard, board);
        int candinum = 3;
        int candi_x[candinum] = {0, 0, 0};
        int candi_y[candinum] = {0, 0, 0};
        int heat[candinum] = {0};
        int curr = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                boolean valid = GameUtil.PutStone(tempBoard, turn, new Position(i, j));
                if (numCandidates != 0 && valid == false) {
                    continue;
                }
                if(heatmap[i][j] > heat[curr]){
                    if(curr < candinum-1){
                        candi_x[curr+1] = candi_x[curr];
                        candi_y[curr+1] = candi_y[curr];
                    }
                    candi_x[curr] = i;
                    candi_y[curr] = j;
                    if(curr < candinum-1) curr++;
                }
            }
        }
        for(int k=0; k<candinum; k++){
            i = candi_x[k];
            j = candi_y[k];
        //for (int i = 0; i < 8; ++i) {
        //    for (int j = 0; j < 8; ++j) {
                copyBoard(tempBoard, board);
                boolean valid = GameUtil.PutStone(tempBoard, turn, new Position(i, j));
                // Allows invalid position when we don't have candidates. Sometimes, player don't
                // have any putable position.
                if (numCandidates != 0 && valid == false) {
                    continue;
                }
                PositionWithOppositeStones next =
                    FindNextPosition(tempBoard, myColor, GameUtil.OppositeColor(turn), level + 1);
                next.position.x = i;
                next.position.y = j;
                if (next.oppositeStones == candidateStones) {
                    candidates[numCandidates++] = next;
                } else if ((myColor == turn && next.oppositeStones < candidateStones) ||
                        (myColor != turn && next.oppositeStones > candidateStones)) {
                    numCandidates = 0;
                    if (valid) {
                        candidateStones = next.oppositeStones;
                    }
                    candidates[numCandidates++] = next;
                }
            }
        }
        return candidates[r.nextInt(numCandidates)];
    }

    public Position GetNextStone(int[][] board, int myColor) {
        return FindNextPosition(board, myColor, myColor, 0).position;
    }
}

private int heatMap[][] = {
    {900,   1,  20,  10,  10,  20,    1, 900},
    {  1,   1,  30,  15,  15,  30,    1,   1},
    { 20,  30,  20,  15,  15,  20,   30,  20},
    { 10,  15,  15,   0,   0,  15,   15,  10},
    { 10,  15,  15,   0,   0,  15,   15,  10},
    { 20,  30,  20,  15,  15,  20,   30,  20},
    {  1,   1,  30,  15,  15,  30,    1,   1},
    {900,   1,  20,  10,  10,  20,    1, 900},
};
