#include "binary_trees.h"

/**
 * binary_tree_height - It measures the height of a binary tree
 * @tree: a pointer to the root node of the tree to measure the height
 * Done by: Mekonen Abera
 *
 * Return: The height of the tree
 *       : If tree is NULL, return 0
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t left, right;

	if (tree == NULL)
		return (0);
	left = binary_tree_height(tree->left);
	right = binary_tree_height(tree->right);
	if (left >= right)
		return (1 + left);
	return (1 + right);
}

/**
 * binary_tree_level - Performs a function on specific level of a binary tree
 * @tree: a pointer to the root of the tree
 * @l: level of the tree to perform a function on
 * @func: a function to be perform
 *
 * Return: void
 */
void binary_tree_level(const binary_tree_t *tree, size_t l, void (*func)(int))
{
	if (tree == NULL)
		return;
	if (l == 1)
		func(tree->n);
	else if (l > 1)
	{
		binary_tree_level(tree->left, l - 1, func);
		binary_tree_level(tree->right, l - 1, func);
	}
}

/**
 * binary_tree_levelorder - Traverses a binary tree using level-order traversal
 * @tree: a pointer to the root node of the tree to traverse
 * @func: a pointer to a function to call for each node
 * Done by: Mekonen Abera
 *
 * Return: void
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	size_t height, i;

	if (tree == NULL || func == NULL)
		return;
	height = binary_tree_height(tree);
	for (i = 1; i <= height; i++)
		binary_tree_level(tree, i, func);
}
/**
 * struct node_s - singly linked list
 * @node: a const binary tree node
 * @next: a points to the next node
 */

typedef struct node_s
{
	const binary_tree_t *node;
	struct node_s *next;
}
ll;

ll *append(ll *head, const binary_tree_t *btnode);
void free_list(ll *head);
ll *get_children(ll *head, const binary_tree_t *parent);
void levels_rec(ll *head, void (*func)(int));

/**
 * binary_tree_levelorder - Goes through a binary tree
 * @tree: a pointer to the root node of the tree to traverse
 *
 * @func: a pointer to a function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	ll *children = NULL;

	func(tree->n);
	children = get_children(children, tree);
	levels_rec(children, func);

	free_list(children);
}

/**
 * levels_rec - Calls func on all nodes at each level.
 * @head: a pointer to head of linked list with nodes at one level.
 * @func: a pointer to a function to call for each node.
 */
void levels_rec(ll *head, void (*func)(int))
{
	ll *children = NULL, *curr = NULL;

	if (!head)
		return;
	for (curr = head; curr != NULL; curr = curr->next)
	{
		func(curr->node->n);
		children = get_children(children, curr->node);
	}
	levels_rec(children, func);
	free_list(children);
}

/**
 * get_children - appends children of parent to linked list.
 * @head: Pointer to head of linked list where children will be appended.
 * @parent: Pointer to node whose children we want to append
 *
 * Return: Pointer to head of linked list of children.
 */
ll *get_children(ll *head, const binary_tree_t *parent)
{
	if (parent->left)
		head = append(head, parent->left);
	if (parent->right)
		head = append(head, parent->right);
	return (head);
}

/**
 * append - It adds a new node at the end of a linkedlist
 * @head: a pointer to head of linked list
 * @btnode: a const binary tree node to append
 *
 * Return: a pointer to head, or NULL on failure
 */
ll *append(ll *head, const binary_tree_t *btnode)
{
	ll *new = NULL, *last = NULL;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->node = btnode;
		new->next = NULL;
		if (!head)
			head = new;
		else
		{
			last = head;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	return (head);
}

/**
 * free_list - frees all the nodes in a linked list
 * @head: pointer to the head of list_t linked list
 */
void free_list(ll *head)
{
	ll *ptr = NULL;

	while (head)
	{
		ptr = head->next;
		free(head);
		head = ptr;
	}
}

