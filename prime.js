console.log("Turing Machine for detecting prime numbers:");

const table = {
    symbols : ['0','1','X','Y','B'],
    finalstate : 6,
    transition : {
        0 : [['1','X','R'],['2','Y','R'],['6','X','R'],['6','Y','R'],['6','B','R']],
        1 : [['1','0','R'],['1','1','R'],['3','X','L'],['3','Y','L'],['3','B','L']],
        2 : [['2','0','R'],['2','1','R'],['4','X','L'],['4','Y','L'],['4','B','L']],
        3 : [['5','X','L'], [] , ['6' ,'X' ,'R'], ['6' ,'Y' ,'R'], []],
        4 : [[] ,['5' ,'Y' ,'L'] ,['6' ,'X' ,'R'], ['6' ,'Y', 'R'],[]], 
        5 : [['5','0','L'],['5','1','L'],['0','X','R'],['0','Y','R'],[]],
        6 : [[],[],[],[],[]],
    },
};

let tape = ['B','1','1','0','0','1','1','B'];
// let tape = ['B','1','1','0','0','1','0','B'];

const compute = (T) => {
    let i=1;
    let s=0;
    let red;
    let tab=[];
    let j=0;
    let map = {};
    T.symbols.forEach(sym => {
        map[sym]=j++;
    });
    while(s!=T.finalstate){
        red = tape[i];
        tab = T.transition[s][map[red]];
        if(tab.length==0){
            console.log("String does not match grammer");
            return;
        }
        s = tab[0];
        tape[i] = tab[1];
        i+= tab[2]=='R'?1:-1;
        tape.forEach(element => {
            process.stdout.write(element+" ");
        });
        console.log("\n");
        for(let it=0;it<tape.length;it++){
            let out = (it==i)?"^ ":"  ";
            process.stdout.write(out);
        }
        console.log("\n");
    }
    console.log("String matches the Grammar");
};

compute(table,tape);
