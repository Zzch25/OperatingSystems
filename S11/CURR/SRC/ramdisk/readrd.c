#include "../sysdef/readrd.h"

void readelems(fs_node_t *fs_in)
{	
	u32int i;
	struct dirent *node;
    for(i=0, node = 0; (node = readdir_fs(fs_in, i)) != 0; i++)
    {
        kout(">");
        kout(node->name);
		kout(": ");
        fs_node_t *fsnode = finddir_fs(fs_in, node->name);

        if ((fsnode->flags&0x7) == FS_DIRECTORY) kout("Directory\n");
        else
        {
            kout("\n\t : \"");
            char buf[256];
            u32int sz = read_fs(fsnode, 0, 256, buf);
            u32int j;
            for (j = 0; j < sz; j++)
                kochr(buf[j]);
            
            kout("\"\n");
        }
    }
}