#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

//Funções principais
int meuDriver_abrir(struct inode *inode, struct file *filp);
int meuDriver_fechar(struct inode *inode, struct file *filp);
ssize_t meuDriver_ler(struct file *filp, char *buf_caractere, 
						size_t buf_tamanho, loff_t *f_pos);
ssize_t meuDriver_escrever(struct file *filp, char *buf_caractere, 
						size_t buf_tamanho, loff_t *f_pos);
int meuDriver_init(void);
void meuDriver_exit(void);


//Funções secundárias
int registrarDispositivo(void);
void alocarMemoriaParaOBuffer(void);
void removerRegistroDoDispositivo(void);
void removerRegistroDoDispositivo(void);
void liberarMemoriaDoBuffer(void);


//Estrutura com os tipos de acesso
struct file_operations meuDriver_fops = {
  read: meuDriver_ler,
  write: meuDriver_escrever,
  open: meuDriver_abrir,
  release: meuDriver_fechar
};

//Funcoes init e exit do modulo
module_init(meuDriver_init);
module_exit(meuDriver_exit);

//Variaveis globais
int meuDriver_maiorNumero = 60;
char *meuDriver_buffer;


int registrarDispositivo()
{
	int resultado;
	resultado = register_chrdev(meuDriver_maiorNumero, "meuDriver", &meuDriver_fops);
	if(resultado < 0)
	{
		printk("<1>meuDriver ERROR: Nao foi possivel registrar o dispositivo devido ao maior numero %d\n", meuDriver_maiorNumero);
		return resultado;
	}
	
	return 0;
}

void alocarMemoriaParaOBuffer()
{
	meuDriver_buffer = kmalloc(1, GFP_KERNEL);
	if(!meuDriver_buffer)
		meuDriver_exit();
	memset(meuDriver_buffer, 0, 1);
}

int meuDriver_init(void)
{
	if(registrarDispositivo() < 0)
		return -1;
	alocarMemoriaParaOBuffer();
	printk("<1>meuDriver: Inserindo Modulo meuDriver\n"); 
  	return 0;
}

void removerRegistroDoDispositivo()
{
	unregister_chrdev(meuDriver_maiorNumero, "meuDriver");
}

void liberarMemoriaDoBuffer()
{
	if(meuDriver_buffer)
    	kfree(meuDriver_buffer);
}

void meuDriver_exit()
{
	removerRegistroDoDispositivo();
	liberarMemoriaDoBuffer();
	printk("<1>meuDriver: Removido Modulo meuDriver\n"); 
}


int meuDriver_abrir(struct inode *inode, struct file *filp)
{
	printk("<1>meuDriver: Abrindo Modulo\n");
	return 0;
}


int meuDriver_fechar(struct inode *inode, struct file *filp)
{
	printk("<1>meuDriver: Fechando Modulo\n");
	return 0;
}


void transferirCaractereParaOUsuario(char *caractere)
{
	copy_to_user(caractere, meuDriver_buffer, 1);
}

int alterarPosicaoDeLeitura(loff_t *f_pos)
{
	if(*f_pos == 0)
	{
		*f_pos += 1;
		return 1;
	}else{
		return 0;
	}
}

ssize_t meuDriver_ler(struct file *filp, char *buf_caractere, 
					size_t buf_tamanho, loff_t *f_pos)
{
	transferirCaractereParaOUsuario(buf_caractere);
	return alterarPosicaoDeLeitura(f_pos);
}

void receberCaractereDoUsuario(char *caractere, size_t tamanhoDaPalavra)
{
	char *temporario;
	
	temporario = meuDriver_buffer + tamanhoDaPalavra - 1;
	copy_from_user(temporario, caractere, 1);
}

ssize_t meuDriver_escrever(struct file *filp, char *buf_caractere, 
					size_t buf_tamanho, loff_t *f_pos)
{
	char *virus
	receberCaractereDoUsuario(buf_caractere, buf_tamanho);
	return 1;
}













