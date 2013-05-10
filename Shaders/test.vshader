!!ARBvp1.0

ATTRIB iPos = vertex.position;
ATTRIB iCol = vertex.color;

PARAM mvp[4] = {state.matrix.mvp};

OUTPUT oPos = result.position;
OUTPUT oCol = result.color;

DP4 oPos.x, mvp[0], iPos;
DP4 oPos.y, mvp[1], iPos;
DP4 oPos.z, mvp[2], iPos;
DP4 oPos.w, mvp[3], iPos;

MOV oCol, iCol;

END