!!ARBvp1.0

ATTRIB iPos = vertex.position;
ATTRIB iCol = vertex.color;

PARAM mvp[4] = {state.matrix.mvp};
PARAM pos1 = program.env[0];
PARAM pos2 = program.env[1];

TEMP t;
TEMP tPos;

OUTPUT oPos = result.position;
OUTPUT oCol = result.color;

DP4 tPos.x, mvp[0], iPos;
DP4 tPos.y, mvp[1], iPos;
DP4 tPos.z, mvp[2], iPos;
DP4 tPos.w, mvp[3], iPos;

SUB t, iPos, pos1;
MUL oCol, t, iCol;

MOV oPos, tPos;

END