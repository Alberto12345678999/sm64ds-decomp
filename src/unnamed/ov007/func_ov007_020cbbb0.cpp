//cpp
#include "types.h"
#include "nitro/fx/fx.h"
#include "cstd.h"
#include "Ov007Spring.h"

extern "C" {

/* Reconstructed layouts and names, not recovered class identity. */

/* The 0x18-byte template (data_ov007_020d7cb0), copied whole into the
 * mesh. Its words, named as in func_ov007_020cba78 and func_ov007_020ca578,
 * which read the copy: [0] every point's mass (Q12), [1]/[2] the spring's
 * stiffness and damping, [3]/[4] pushMin/pushMax, [5] the z every point is
 * built at. They stay one array: the copy below is a single ldm/stm block,
 * and a struct of six named ints copies word by word. */
typedef struct Ov007MeshParams {
    int words[6];
} Ov007MeshParams;

/* data_ov007_02104bd4[0], the 0x38-byte grid mesh; names as in
 * func_ov007_020ca5f0. */
typedef struct Ov007Mesh {
    Vector3 *verts;         /* 0x00: one per grid point */
    Ov007Grid *grid;        /* 0x04 */
    void **cellLinks;       /* 0x08: one func_ov007_020c80a4 link per cell */
    Ov007MeshParams params; /* 0x0c */
    short cellWidth;        /* 0x24: column spacing */
    short cellHeight;       /* 0x26: row spacing */
    int *faceNormals;       /* 0x28: s16 triple per triangle, two per cell */
    int *vertexNormals;     /* 0x2c: s16 triple per point */
    int *texOffsetS;        /* 0x30: one per column */
    int *texOffsetT;        /* 0x34 */
} Ov007Mesh;

typedef char Ov007Mesh_size_must_be_0x38[sizeof(Ov007Mesh) == 0x38 ? 1 : -1];

extern void *func_ov007_020c3df4(int a, int size);
extern void *func_ov007_020c73f0(int a, int b, int c, int d);
extern Ov007Link *func_ov007_020c80a4(void);
extern void func_ov007_020c72d0(void *g);
extern void func_ov007_020c8010(void *node, void *a, void *b);
extern void func_ov007_020cb3dc(void *ctx);

/* Builds a columns x rows mesh `width` wide, centred on the origin, every
 * point at the template's rest z. Rows are cellHeight apart (width *
 * sqrt(2) / 2 over the columns - 1 cells), odd rows shifted half a cell
 * along x, and the border points are pinned. Each cell gets a link across
 * its diagonal, which alternates with the row. The link pass reuses
 * `columns` as the row's first cell index. */
void *func_ov007_020cbbb0(int columns, int rows, int width, Ov007MeshParams *params) {
    int cellWidth, cellHeight, t, halfWidth, halfHeight, cellRows, cellColumns, j, i, k, i2;
    Ov007Mesh *mesh;

    mesh = (Ov007Mesh *)func_ov007_020c3df4(0, sizeof(Ov007Mesh));
    cellColumns = columns - 1;
    cellWidth = (int)cstd::div(width, cellColumns);
    t = FX_MUL(width, 0x16a1);
    cellHeight = (int)cstd::div(t / 2, cellColumns);
    {
        int n = columns - 1;
        cellColumns = n;
    }
    halfWidth = (cellWidth * cellColumns) / 2;
    cellRows = rows - 1;
    halfHeight = (cellHeight * cellRows) / 2;
    mesh->verts = (Vector3 *)func_ov007_020c3df4(0, columns * 12 * rows);
    mesh->faceNormals = (int *)func_ov007_020c3df4(0, cellColumns * 6 * cellRows * 2);
    mesh->vertexNormals = (int *)func_ov007_020c3df4(0, columns * 6 * rows);
    mesh->texOffsetS = (int *)func_ov007_020c3df4(0, columns * 4);
    mesh->texOffsetT = (int *)func_ov007_020c3df4(0, columns * 4);
    mesh->cellWidth = (short)cellWidth;
    mesh->cellHeight = (short)cellHeight;
    mesh->cellLinks = (void **)func_ov007_020c3df4(0, cellColumns * 0x18 * cellRows);
    mesh->grid = (Ov007Grid *)func_ov007_020c73f0(3, columns, rows, params->words[0]);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            Vector3 *elem = &mesh->verts[i * columns + j];
            elem->x = j * cellWidth - halfWidth + ((i % 2 == 0) ? 0 : cellWidth / 2);
            elem->y = cellHeight * (rows - 1 - i) - halfHeight;
            elem->z = params->words[5];
            mesh->grid->rowLists[i]->items[j]->target = elem;
            if (j < cellColumns && i < cellRows) {
                mesh->cellLinks[i * cellColumns + j] = func_ov007_020c80a4();
            }
            if (j == 0 || j == columns - 1 || i == 0 || i == rows - 1) {
                mesh->grid->rowLists[i]->items[j]->flags |= 1;
            }
        }
    }

    func_ov007_020c72d0(mesh->grid);

    {
        i = 0;
        if (cellRows > 0) {
            columns = i;
            do {
                j = 0;
                if (cellColumns > 0) {
                    do {
                        int i2mod = i % 2;
                        int t = i2mod;
                        int i2p1 = i + 1;
                        int sum = j + columns;
                        if (i2mod == 0) {
                            Ov007Grid *g = mesh->grid;
                            void **links = mesh->cellLinks;
                            void *link = links[sum];
                            void *ea = g->rowLists[i]->items[j + 1];
                            void *eb = g->rowLists[i2p1]->items[j];
                            func_ov007_020c8010(link, ea, eb);
                        } else {
                            Ov007Grid *g = mesh->grid;
                            void **links = mesh->cellLinks;
                            void *link = links[sum];
                            void *ea = g->rowLists[i]->items[j];
                            void *eb = g->rowLists[i2p1]->items[j + 1];
                            func_ov007_020c8010(link, ea, eb);
                        }
                        j++;
                    } while (j < cellColumns);
                }
                i++;
                columns += cellColumns;
            } while (i < cellRows);
        }
    }

    mesh->params = *params;
    func_ov007_020cb3dc(mesh);
    return mesh;
}
}
