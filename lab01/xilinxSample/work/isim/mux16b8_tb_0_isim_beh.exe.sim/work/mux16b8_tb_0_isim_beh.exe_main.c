/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    unisims_ver_m_00000000002549801008_4245414866_init();
    unisims_ver_m_00000000001461499759_1414817250_init();
    unisims_ver_m_00000000002123152668_0970595058_init();
    work_m_00000000001340165503_4001557595_init();
    unisims_ver_m_00000000001944113200_1791843267_init();
    unisims_ver_m_00000000001844249156_2674322954_init();
    work_m_00000000001738509090_3113700453_init();
    unisims_ver_m_00000000003927721830_1593237687_init();
    work_m_00000000003850176458_2855506826_init();
    work_m_00000000002086198925_1497582709_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000002086198925_1497582709");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
