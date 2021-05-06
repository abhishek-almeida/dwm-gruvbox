syntax enable
set number
set wildmenu
set relativenumber
set hlsearch
set ignorecase
set incsearch
set mouse+=a
set noexpandtab
set nosmarttab
set tabstop=8
set softtabstop=2
set shiftwidth=2
filetype plugin indent on
set laststatus=2
set noshowmode
set statusline=%!StatusLine()

call plug#begin()
Plug 'preservim/nerdtree'
Plug 'tpope/vim-surround'
Plug 'tpope/vim-commentary'
Plug 'mattn/emmet-vim'
Plug 'morhetz/gruvbox'
call plug#end()
let g:gruvbox_termcolors=16
colorscheme gruvbox



hi User1 ctermfg=0 ctermbg=3
hi User2 ctermfg=0 ctermbg=6
hi User3 ctermfg=0 ctermbg=5
hi User4 ctermfg=0 ctermbg=2
hi User5 ctermfg=15 ctermbg=0

function! StatusLine()
  let l:mode=mode()
  let l1="%5*\ %F\ %r%m%="
  let l2= b:gitbranch
  let l3="\ %y\ "
  let l4 = l1 . l2 . l3
  let l5 = "\ [%l/%L]\ [%p%%]\ "
  if l:mode==#"n"
    return "%1*\ NORMAL\ " . l4 . "%1*" . l5
  elseif l:mode==?"v"
    return "%3*\ VISUAL\ " . l4 . "%3*" . l5
  elseif l:mode==?"\<C-V>"
    return "%3*\ VISUAL\ " . l4 . "%3*" . l5
  elseif l:mode==#"i"
    return "%2*\ INSERT\ " . l4 . "%2*" . l5
  elseif l:mode==#"R"
    return "%2*\ REPLACE\ " . l4 . "%2*" . l5
  elseif l:mode==#"c"
    return "%4*\ COMMAND\ " . l4 . "%4*" . l5
  endif
endfunction

function! StatusLineGitBranch()
  let b:gitbranch=""
  if &modifiable
    try
      let l:dir=expand('%:p:h')
      let l:gitrevparse = system("git -C ".l:dir." rev-parse --abbrev-ref HEAD")
      if !v:shell_error
	let b:gitbranch="[".substitute(l:gitrevparse, '\n', '', 'g')."]"
      endif
    catch
    endtry
  endif
endfunction

augroup GetGitBranch
  autocmd!
  autocmd VimEnter,WinEnter,BufEnter * call StatusLineGitBranch()
augroup END

" " Copy to clipboard
vnoremap  <leader>y  "+y
nnoremap  <leader>Y  "+yg_
nnoremap  <leader>y  "+y
nnoremap  <leader>yy  "+yy

" " Paste from clipboard
nnoremap <leader>p "+p
nnoremap <leader>P "+P
vnoremap <leader>p "+p
vnoremap <leader>P "+P


" Disabling arrow keys"	
" noremap <Up> <Nop>
"noremap <Down> <Nop>
"noremap <Left> <Nop>
"noremap <Right> <Nop>
"noremap <backspace> <Nop>


let g:user_emmet_mode='n'    "only enable normal mode functions.
let g:user_emmet_leader_key=','	
let g:NERDTreeDirArrowExpandable="+"
let g:NERDTreeDirArrowCollapsible="~"
map <Space> :NERDTreeToggle<CR>
let NERDTreeStatusline='%1* %{exists("b:NERDTree")?b:NERDTree.root.path.str():""} %5*'


